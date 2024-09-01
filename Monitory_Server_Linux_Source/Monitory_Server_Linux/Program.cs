using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;

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

        private static bool _turbostatCommandRunning;
        private static float _currentCpuWatt = 0.0f;
        private static float _currentCpuTemp = 0.0f;

        private readonly TcpListener _server = new TcpListener(IPAddress.Any, 54000);

        static void Main()
        {
            Console.WriteLine("Thanks a lot for coming that far...");

            bool bNeedExit = false;
            Program main = new Program();
            main.server_start(); //starting the server

            while (!bNeedExit)
            {
                try
                {
                    if (!_turbostatCommandRunning)
                    {
                        _turbostatCommandRunning = true;
                        Thread thread = new Thread(() =>
                        {
                            try
                            {
                                string file = Path.Combine(Directory.GetCurrentDirectory(), "turbostat_info.txt");
                                string command =
                                    "turbostat --quiet  --num_iterations=1    --interval=0.5     --out=" +
                                    AddQuote() + file + AddQuote();
                                _lastCpuUtilString =
                                    RunCommand("bash", "-c " + AddQuote() + command + AddQuote(), true);
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e);
                            }

                            _turbostatCommandRunning = false;
                        });
                        thread.Start();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                    throw;
                }

                try
                {
                    if (!_cpuUtilThreadRunning)
                    {
                        _cpuUtilThreadRunning = true;
                        Thread thread = new Thread(() =>
                        {
                            try
                            {
                                _lastCpuUtilString = RunCommand("bash", "-c \"mpstat -P ALL 1 1\"");
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e);
                            }

                            _cpuUtilThreadRunning = false;
                        });
                        thread.Start();
                    }

                    if (!_drivesThreadRunning)
                    {
                        _drivesThreadRunning = true;
                        Thread thread = new Thread(() =>
                        {
                            try
                            {
                                _lastDrivesUtilString = RunCommand("bash", "-c \"iostat -d -x 1 2\"");
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e);
                            }

                            _drivesThreadRunning = false;
                        });
                        thread.Start();
                    }

                    if (!_networkInfoThreadRunning)
                    {
                        _networkInfoThreadRunning = true;
                        Thread thread = new Thread(() =>
                        {
                            try
                            {
                                _lastNetworkUtilString = RunCommand("bash", "-c \"ifstat -nt -T 1 1\"");
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e);
                            }

                            _networkInfoThreadRunning = false;
                        });
                        thread.Start();
                    }

                    _dataToSend = CollectData();
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }

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

        public static string AddQuote()
        {
            return "\"";
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

        static string RunCommand(string command, string arguments, bool useShell = false)
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
                string line = $"Cpu_Utility:Total:0:0:100|";
                properties += line;

                string line1 = $"Cpu_Utility:0:0:0:100|";
                properties += line1;
                return;
            }

            //Console.WriteLine(utilityString);

            string[] splittedUtilityString = _lastCpuUtilString.Split(new[] { Environment.NewLine },
                StringSplitOptions.RemoveEmptyEntries);

            if (splittedUtilityString.Length > 2)
            {
                string[] allCpuRow = splittedUtilityString[2].Split(' ', StringSplitOptions.RemoveEmptyEntries)
                    ;
                //string utilityValue = allCpuRow[allCpuRow.Length - 1].Replace(',', '.');
                float parseValue = 0;
                float.TryParse(allCpuRow[allCpuRow.Length - 1].Replace(',', '.'), out parseValue);

                float allUtility = 100f - parseValue;

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
                float parseValue = 0;
                float.TryParse(cpuRow[cpuRow.Length - 1].Replace(',', '.'), out parseValue);

                float utility = 100f - parseValue;

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
                float mhzFloat = 0;
                float.TryParse(mhz.Replace(',', '.'), out mhzFloat);

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
                float.TryParse(splittedRamString[0].Replace(',', '.'), out ramFloatAvailableFull);
            }

            float ramFloatUsed = 0;
            if (splittedRamString.Length >= 2)
            {
                float.TryParse(splittedRamString[1].Replace(',', '.'), out ramFloatUsed);
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

                float drivesFloat = 0;
                float.TryParse(driveRow[driveRow.Length - 1].Replace(',', '.'), out drivesFloat);

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

            if (splittedNetworkString.Length <= 2) return;

            string[] networkRow = splittedNetworkString[2]
                .Split(' ', StringSplitOptions.RemoveEmptyEntries);

            string[] networkRowNames = splittedNetworkString[0]
                .Split(' ', StringSplitOptions.RemoveEmptyEntries);

            int iterationIdx = 1;
            float maxDownload = 0;
            float.TryParse(networkRow[networkRow.Length - 1].Replace(',', '.'), out maxDownload);
            maxDownload *= 1024;
            float maxUpload = 0;
            float.TryParse(networkRow[networkRow.Length - 2].Replace(',', '.'), out maxUpload);
            maxUpload *= 1024;
            while (networkRow.Length > iterationIdx + 2)
            {
                int nameIdx = (iterationIdx - 1) / 2 + 1;

                // Console.WriteLine(nameIdx);
                //  Console.WriteLine(iterationIdx);

                float upFloat = 0;
                float.TryParse(networkRow[iterationIdx + 1].Replace(',', '.'), out upFloat);
                upFloat *= 1024;

                string upload =
                    $"Upload_Speed:{networkRowNames[nameIdx]}:{upFloat}:0:{maxUpload}|";
                properties += upload;

                float downFloat = 0;
                float.TryParse(networkRow[iterationIdx].Replace(',', '.'), out downFloat);
                downFloat *= 1024;

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
            string file = Path.Combine(Directory.GetCurrentDirectory(), "turbostat_info.txt");
            // string wattageString = RunCommand("bash", $"-c \"cat \"{file}\"");
            // string tempString = RunSudoCommand("bash", "-c \"sudo turbostat --quiet --show PkgTmp 1 1\"");

            float pkgTmp = 0.0f;
            float pkgWatt = 0.0f;

            string[] stat_file = File.ReadAllLines(file);
            for (int i = stat_file.Length - 1; i >= 0; i--)
            {
                if (stat_file[i].Contains("PkgTmp") && stat_file[i].Contains("PkgWatt"))
                {
                    string[] info_lines = stat_file[i].Trim()
                        .Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                    string[] data_lines = stat_file[i + 1].Trim()
                        .Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                    for (int item = info_lines.Length - 1; item >= 0; item--)
                    {
                        if (info_lines[item] == "PkgTmp")
                        {
                            float tmp = 0.0f;
                            float.TryParse(data_lines[item].Replace(',', '.'), out tmp);
                            if (tmp == 0.0f)
                            {
                                pkgTmp = _currentCpuTemp;
                            }
                            else
                            {
                                pkgTmp = tmp;
                                _currentCpuTemp = tmp;
                            }
                        }

                        if (info_lines[item] == "PkgWatt")
                        {
                            float watt = 0.0f;
                            float.TryParse(data_lines[item].Replace(',', '.'), out watt);
                            if (watt == 0.0f)
                            {
                                pkgWatt = _currentCpuWatt;
                            }
                            else
                            {
                                pkgWatt = watt;
                                _currentCpuWatt = watt;
                            }
                        }
                    }

                    break;
                }
            }

            if (pkgTmp == 0.0f)
            {
                pkgTmp = _currentCpuTemp;
            }
            if (pkgWatt == 0.0f)
            {
                pkgWatt = _currentCpuWatt;
            }

            properties += $"Wattage:{name}:{pkgWatt}:0:100|";
            properties += $"Temperature:{name}:{pkgTmp}:0:100|";
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

            float gpuUtil = 0;
            float.TryParse(utility.Replace(',', '.'), out gpuUtil);

            float gpuClock = 0;
            float.TryParse(clock.Replace(',', '.'), out gpuClock);

            float gpuMemAvailable = 0;
            float.TryParse(freeMem.Replace(',', '.'), out gpuMemAvailable);
            gpuMemAvailable /= 1000;

            float gpuMemUsed = 0;
            float.TryParse(usedMem.Replace(',', '.'), out gpuMemUsed);
            gpuMemUsed /= 1000;

            float gpuWatt = 0;
            float.TryParse(watt.Replace(',', '.'), out gpuWatt);

            float gpuTemp = 0;
            float.TryParse(temp.Replace(',', '.'), out gpuTemp);

            properties += $"Gpu_Utility:Clock:{gpuUtil}:0:100|";
            properties += $"Gpu_Clock:Clock:{gpuClock}:0:100|";
            properties += $"Gpu_Memory:Available:{gpuMemAvailable}:0:100|";
            properties += $"Gpu_Memory:Used:{gpuMemUsed}:0:100|";
            properties += $"Wattage:{name}:{gpuWatt}:0:100|";
            properties += $"Temperature:{name}:{gpuTemp}:0:100|";
        }
    }
}