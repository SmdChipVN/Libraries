using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FileManager;

namespace Test
{
    class test_object
    {
        [CustomAttribute(FileRender = true)]
        public int version { get; set; }
    }
}
