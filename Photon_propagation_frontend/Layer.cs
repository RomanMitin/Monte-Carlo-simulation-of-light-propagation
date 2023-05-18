using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Photon_propagation_frontend
{
    public class Layer_t
    {
        public Layer_t() 
        {
            n = z0 = z1 = mua = mus = g = double.NaN;
        }

        public double n { get; set; }
        public double z0 { get; set; }
        public double z1 { get; set; }
        public double mua { get; set; }
        public double mus { get; set; }
        public double g { get; set; }

        public enum ID
        {
            idn = 1, idz1, idmua, idmus, idg
        }
    }
}
