using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Photon_propagation_frontend
{
    internal class InputBinFile
    {
        static public double[,] GetMatrixFromFile(string inputBinFileName)
        {
            if (File.Exists(inputBinFileName))
            {
                UInt64 size_c, size_r;
                double[,] result;

                var file = File.OpenRead(inputBinFileName);

                BinaryReader br = new BinaryReader(file);
                size_c = br.ReadUInt64();
                size_r = br.ReadUInt64();

                result = new double[size_r, size_c];

                for (UInt64 i = 0; i < size_r; i++)
                {
                    for (UInt64 j = 0; j < size_c; j++)
                    {
                        result[i,j] = br.ReadDouble();
                    }
                }

                file.Close();

                return result;

            }
            else
            {
                throw new Exception("No output file");
            }
        }
    }
}
