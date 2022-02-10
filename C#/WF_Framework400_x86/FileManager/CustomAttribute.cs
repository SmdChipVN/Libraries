using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FileManager
{
    public class CustomAttribute : Attribute
    {
        public bool FileRender { get; set; } = false;
        public bool ReadOnly { get; set; } = false;
        public bool Hidden { get; set; } = false;
        public bool CustomRender { get; set; } = false;
    }
}
