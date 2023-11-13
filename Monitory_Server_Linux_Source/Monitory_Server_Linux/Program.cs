//using System; // Importing the System namespace

using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;

//using System.Numerics;

//using System.Threading;

namespace Monitory_Server_Linux
{
    class Program
    {
        private static string _dataToSend = "";
        private static bool _cpuUtilThreadRunning;
        private static string _lastCpuUtilString = "";
        private static string _lastDrivesUtilString = "";
        private static bool _drivesThreadRunning;
        private static string _lastNetworkUtilString = "";
        private static bool _networkInfoThreadRunning;

        private readonly TcpListener _server = new TcpListener(IPAddress.Any, 54000);

        static void Main()
        {
            Console.WriteLine("Thanks a lot for coming that far...");

            bool bNeedExit = false;
            Program main = new Program();
            main.server_start(); //starting the server

            while (!bNeedExit)
            {
                if (!_cpuUtilThreadRunning)
                {
                    _cpuUtilThreadRunning = true;
                    Thread thread = new Thread(() =>
                    {
                        _lastCpuUtilString = RunCommand("bash", "-c \"mpstat -P ALL 1 1\"");

                        _cpuUtilThreadRunning = false;
                    });
                    thread.Start();
                }

                if (!_drivesThreadRunning)
                {
                    _drivesThreadRunning = true;
                    Thread thread = new Thread(() =>
                    {
                        _lastDrivesUtilString = RunCommand("bash", "-c \"iostat -d -x 1 2\"");

                        _drivesThreadRunning = false;
                    });
                    thread.Start();
                }

                if (!_networkInfoThreadRunning)
                {
                    _networkInfoThreadRunning = true;
                    Thread thread = new Thread(() =>
                    {
                        _lastNetworkUtilString = RunCommand("bash", "-c \"ifstat -nt -T 1 1\"");

                        _networkInfoThreadRunning = false;
                    });
                    thread.Start();
                }

                _dataToSend = CollectData();
                //Console.WriteLine(DataToSend);
                Thread.Sleep(300);
            }

            Console.WriteLine("Press any key to exit...");

            // Wait for a key press
            Console.ReadKey();

            Console.WriteLine("Exiting the program.");
        }

        private void server_start()
        {
            _server.Start();
            accept_connection(); //accepts incoming connections
        }

        private void accept_connection()
        {
            _server.BeginAcceptTcpClient(handle_connection,
                _server); //this is called asynchronously and will run in a different thread
        }

        private void
            handle_connection(IAsyncResult result) //the parameter is a delegate, used to communicate between threads
        {
            accept_connection(); //once again, checking for any other incoming connections
            TcpClient client = _server.EndAcceptTcpClient(result); //creates the TcpClient

            NetworkStream ns = client.GetStream();

            /* here you can add the code to send/receive data */

            Console.WriteLine("Client Connected");

            try
            {
                while (client.Connected) //while the client is connected, we look for incoming messages
                {
                    string hiMessage = _dataToSend;
                    byte[] hiBytes = Encoding.Default.GetBytes(hiMessage);
                    ns.Write(hiBytes, 0, hiBytes.Length);

                    Thread.Sleep(300);
                }
            }
            catch (Exception)
            {
                Console.WriteLine("Client Disconnected");
            }
            finally
            {
                client.Dispose();
                client.Close();
                ns.Dispose();
                ns.Close();
            }
        }


        static string CollectData()
        {
            string data = "";

            string timeNow = $"Time_Now:{DateTime.Now.ToString("HH~mm")}:0:0:0|";
            data += timeNow;

            string dateNow = $"Date_Now:{DateTime.Now.ToShortDateString()}:0:0:0|";
            data += dateNow;

            CollectCpuLoadAndClockData(ref data);

            CollectMemoryData(ref data);

            CollectStorageData(ref data);

            CollectNetworkData(ref data);

            CollectCpuData(ref data);

            CollectGpuData(ref data);

            return data;
        }

        static string RunCommand(string command, string arguments)
        {
            string output = "";

            try
            {
                ProcessStartInfo psi = new ProcessStartInfo(command)
                {
                    RedirectStandardOutput = true,
                    UseShellExecute = false,
                    CreateNoWindow = true,
                    Arguments = arguments
                };

                using (Process process = new Process { StartInfo = psi })
                {
                    process.Start();

                    using (StreamReader reader = process.StandardOutput)
                    {
                        output = reader.ReadToEnd();
                    }

                    process.WaitForExit();
                }
            }
            catch (Exception ex)
            {
                // Handle any exceptions that may occur during the process execution
                output = "Error running command: " + ex.Message;
            }

            return output;
        }


        public static void CollectCpuLoadAndClockData(ref string properties)
        {
            // string utilityString = _lastCpuUtilString;//RunCommand("bash", "-c \"mpstat -P ALL 1 1\"");

            if (_lastCpuUtilString == "")
            {
                return;
            }

            //Console.WriteLine(utilityString);

            string[] splittedUtilityString = _lastCpuUtilString.Split(new[] { Environment.NewLine },
                StringSplitOptions.RemoveEmptyEntries);

            if (splittedUtilityString.Length > 2)
            {
                string[] allCpuRow = splittedUtilityString[2].Split(' ', StringSplitOptions.RemoveEmptyEntries)
                    ;
                //Console.WriteLine(allUltilitystrings[allUltilitystrings.Length - 1]);

                float allUtility = 100f - float.Parse(allCpuRow[allCpuRow.Length - 1].Replace(',', '.'));

                string line = $"Cpu_Utility:Total:{allUtility}:0:100|";
                properties += line;
            }

            // int lastValidIndex = 3;
            int threadIndex = 0;
            while (splittedUtilityString.Length > threadIndex + 3)
            {
                string[] cpuRow = splittedUtilityString[3 + threadIndex]
                        .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                    ;


                if (cpuRow[0][0] == 'A')
                {
                    break;
                }

                // Console.WriteLine(ultilitystrings[ultilitystrings.Length - 1]);

                float utility = 100f - float.Parse(cpuRow[cpuRow.Length - 1].Replace(',', '.'));

                string line = $"Cpu_Utility:{threadIndex}:{utility}:0:100|";
                properties += line;

                //lastValidIndex ++;
                threadIndex++;
            }


            string mhzString = RunCommand("bash", "-c \"cat /proc/cpuinfo | grep 'MHz' | uniq | awk '{print $4}'\"");

            string[] splittedMhzString = mhzString.Split(new[] { Environment.NewLine },
                StringSplitOptions.RemoveEmptyEntries);

            int mhzThreadIdx = 0;
            float averageMhz = -1f;
            foreach (var mhz in splittedMhzString)
            {
                float mhzFloat = float.Parse(mhz.Replace(',', '.'));

                string line = $"Cpu_Clock:{mhzThreadIdx}:{mhzFloat}:0:100|";
                properties += line;

                if (averageMhz < -0.5f)
                {
                    averageMhz = mhzFloat;
                }
                else
                {
                    averageMhz = (averageMhz + mhzFloat) * 0.5f;
                }
            }

            string cpuClockTotal = $"Cpu_Clock:Total:{averageMhz}:0:100|";
            properties += cpuClockTotal;
        }

        public static void CollectMemoryData(ref string properties)
        {
            string ramString = RunCommand("bash", "-c \"free -m | awk '/^Mem/ {print $2/1000 \\\"\\n\\\" $3/1000}'\"");
            // Console.WriteLine(ramString);

            string[] splittedRamString = ramString.Split(new[] { Environment.NewLine },
                StringSplitOptions.RemoveEmptyEntries);

            float ramFloatAvailableFull = 0;
            if (splittedRamString.Length >= 1)
            {
                ramFloatAvailableFull = float.Parse(splittedRamString[0].Replace(',', '.'));
            }

            float ramFloatUsed = 0;
            if (splittedRamString.Length >= 2)
            {
                //Console.WriteLine(splittedRamString[1]);
                ramFloatUsed = float.Parse(splittedRamString[1].Replace(',', '.'));
                string line = $"Cpu_Memory:Used:{ramFloatUsed}:0:100|";
                properties += line;
            }

            properties += $"Cpu_Memory:Available:{ramFloatAvailableFull - ramFloatUsed}:0:100|";
            ;
        }

        public static void CollectStorageData(ref string properties)
        {
            // string drivestring = _lastDrivesUtilString;//RunCommand("bash", "-c \"iostat -d -u 0.1 2\"");

            if (_lastDrivesUtilString == "")
            {
                return;
            }

            string[] splittedDrivesString = _lastDrivesUtilString.Split(new[] { Environment.NewLine },
                StringSplitOptions.RemoveEmptyEntries);

            int iterationIndex = 4;
            while (splittedDrivesString.Length > iterationIndex)
            {
                string[] driveRow = splittedDrivesString[iterationIndex]
                        .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                    ;

                iterationIndex++;

                if (driveRow[driveRow.Length - 1].ToLower().Contains("%util"))
                {
                    break;
                }
            }

            while (splittedDrivesString.Length > iterationIndex)
            {
                string[] driveRow = splittedDrivesString[iterationIndex]
                        .Split(' ', StringSplitOptions.RemoveEmptyEntries)
                    ;

                if (driveRow[0].ToLower().Contains("loop"))
                {
                    iterationIndex++;
                    continue;
                }

                float drivesFloat = float.Parse(driveRow[driveRow.Length - 1].Replace(',', '.'));

                string storage = $"Storage_Load:{driveRow[0]}:{drivesFloat}:0:100|";
                properties += storage;

                //Console.WriteLine(drivesFloat);

                iterationIndex++;
            }

            //Console.WriteLine(drivestring);
        }


        public static void CollectNetworkData(ref string properties)
        {
            if (_lastNetworkUtilString == "")
            {
                return;
            }

            string[] splittedNetworkString = _lastNetworkUtilString.Split(new[] { Environment.NewLine },
                StringSplitOptions.RemoveEmptyEntries);

            string[] networkRow = splittedNetworkString[2]
                .Split(' ', StringSplitOptions.RemoveEmptyEntries);

            string[] networkRowNames = splittedNetworkString[0]
                .Split(' ', StringSplitOptions.RemoveEmptyEntries);

            int iterationIdx = 1;
            float maxDownload = float.Parse(networkRow[networkRow.Length - 1].Replace(',', '.')) * 1024;
            float maxUpload = float.Parse(networkRow[networkRow.Length - 2].Replace(',', '.')) * 1024;
            while (networkRow.Length > iterationIdx + 2)
            {
                int nameIdx = (iterationIdx - 1) / 2 + 1;

                // Console.WriteLine(nameIdx);
                //  Console.WriteLine(iterationIdx);

                float upFloat = float.Parse(networkRow[iterationIdx + 1].Replace(',', '.')) * 1024;

                string upload =
                    $"Upload_Speed:{networkRowNames[nameIdx]}:{upFloat}:0:{maxUpload}|";
                properties += upload;

                float downFloat = float.Parse(networkRow[iterationIdx].Replace(',', '.')) * 1024;

                string download =
                    $"Download_Speed:{networkRowNames[nameIdx]}:{downFloat}:0:{maxDownload}|";
                properties += download;

                iterationIdx += 2;
            }
        }

        public static void CollectCpuData(ref string properties)
        {
            string name = RunCommand("bash",
                "-c \"lscpu | grep 'Model name' | awk -F ':' '{print $2}' | awk '{$1=$1};1'\"");
            //string wattageString = RunCommand("turbostat", "--show PkgWatt 1 1");
            // string tempString = RunCommand("bash", "-c \"sudo turbostat --quiet --show PkgTmp 1 1\"");

            //Console.WriteLine(wattageString);

            //string[] wattage = wattageString.Split(new[] { Environment.NewLine }, StringSplitOptions.None);
            // string[] temp = tempString.Split(new[] { Environment.NewLine }, StringSplitOptions.None);

            //Console.WriteLine(wattage.Length);
            //Console.WriteLine("This is the String ->" + wattageString);

            // TODO:
            
            properties += $"Wattage:{name}:0:0:100|";
            properties += $"Temperature:{name}::0:0:100|";
        }

        public static void CollectGpuData(ref string properties)
        {
            string name = RunCommand("bash", "-c \"nvidia-smi --query-gpu=name --format=csv,noheader\"");
            string utility = RunCommand("bash",
                "-c \"nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits\"");
            string clock = RunCommand("bash", "-c \"nvidia-smi --query-gpu=clocks.gr --format=csv,noheader,nounits\"");
            string freeMem = RunCommand("bash",
                "-c \"nvidia-smi --query-gpu=memory.free --format=csv,noheader,nounits\"");
            string usedMem = RunCommand("bash",
                "-c \"nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits\"");
            string temp = RunCommand("bash", "-c \"nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader\"");
            string watt = RunCommand("bash", "-c \"nvidia-smi --query-gpu=power.draw --format=csv,noheader,nounits\"");

            properties += $"Gpu_Utility:Clock:{float.Parse(utility.Replace(',', '.'))}:0:100|";
            properties += $"Gpu_Clock:Clock:{float.Parse(clock.Replace(',', '.'))}:0:100|";
            properties += $"Gpu_Memory:Available:{float.Parse(freeMem.Replace(',', '.')) / 1000}:0:100|";
            properties += $"Gpu_Memory:Used:{float.Parse(usedMem.Replace(',', '.')) / 1000}:0:100|";
            properties += $"Wattage:{name}:{float.Parse(watt.Replace(',', '.'))}:0:100|";
            properties += $"Temperature:{name}:{float.Parse(temp.Replace(',', '.'))}:0:100|";
        }
    }
}