#include <Loadcell.h>

static bool _Fill(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell)
{
  signed long calib_mass_x10 = Info->ReadCalibMass() / 30;
  unsigned short count_stability = 0;
  signed long last_value = -1;
  unsigned short time = 0;
  while (count_stability < 10)
  {
    signed long value;
    while (!(Info->GetValue(&value)))
    {
      if (time++ > Info->TimeOut)
        return false;
      LOADCELL_DELAY_1MS();
    }    
    time = 0;
    if (((last_value - value) > calib_mass_x10) || ((value - last_value) > calib_mass_x10))
      count_stability = 0;
    else
      count_stability++;
    last_value = value;
  }
  Loadcell->Accumulator = 0;
  for (unsigned char i = 0; i < LOADCELL_BUFF_SIZE; i++)
  {
    while (!(Info->GetValue(&Loadcell->Buffer[i])))
    {
      if (time++ > Info->TimeOut)
        return false;
      LOADCELL_DELAY_1MS();
    }    
    Loadcell->Accumulator += Loadcell->Buffer[i];
    time = 0;
  }
  Loadcell->Index = 0;
  return true;
}

bool Loadcell_Begin(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell)
{
  if (Info->ReadCalibMass() == 0)
    return false;  
  return Loadcell_CalibZero(Info, Loadcell);
}

signed long Loadcell_Mass(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell)
{
  signed long calib_mass;
  calib_mass = Info->ReadCalibMass();
  if (calib_mass == 0)
    return -1;
  return (Loadcell->Zero - (Loadcell->Accumulator / LOADCELL_BUFF_SIZE)) * LOADCELL_CALIB_MASS / calib_mass;
}

bool Loadcell_CalibZero(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell)
{
#ifdef LOADCELL_CALIB_ABSOLUTE
  if (!_Fill(Info, Loadcell))
    return false;
#endif
  Loadcell->Zero = Loadcell->Accumulator / LOADCELL_BUFF_SIZE;
  return true;
}

bool Loadcell_CalibMass(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell)
{
  signed long calib_mass;
#ifdef LOADCELL_CALIB_ABSOLUTE
  if (!_Fill(Info, Loadcell))
    return false;
#endif
  calib_mass = Loadcell->Zero - (Loadcell->Accumulator / LOADCELL_BUFF_SIZE);
  Info->SaveCalibMass(calib_mass);
  return true;
}

bool Loadcell_Read(const LoadcellInfo_TypeDef* Info, Loadcell_TypeDef* Loadcell)
{
  signed long value;  
  if (Info->GetValue(&value))
  {
    Loadcell->Accumulator -= Loadcell->Buffer[Loadcell->Index];
    Loadcell->Buffer[Loadcell->Index] = value;
    Loadcell->Accumulator += value;
    Loadcell->Index = (Loadcell->Index + 1) % LOADCELL_BUFF_SIZE;
    return true;
  }
  return false;
}