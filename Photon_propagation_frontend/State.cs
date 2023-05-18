using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Photon_propagation_frontend
{
    public class State_t
    {
        public State_t() { }

        public List<Layer_t> layers { get; set; }

        public double dr { get; set; }
        public double dz { get; set; }

        public double lenght_r { get; set; }

        public UInt64 Photon_num { get; set; }
        public UInt32 Thread_num { get; set; }
        public double Critical_weight { get; set; }
    }
}
