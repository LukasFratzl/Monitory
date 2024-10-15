using System.Collections.Concurrent;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;

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
        private static string _currentCPUName = "Compute Unit";
        private static string _currentGPUName = "Graphics";

        private readonly TcpListener _server = new TcpListener(IPAddress.Any, 54000);
        private static Dictionary<Commands, string> _commands = new Dictionary<Commands, string>();

        public enum Commands
        {
            CPU_MHZ_STR,
            RAM_STR,
            CPU_NAME,
            GPU_NAME,
            GPU_UTIL,
            GPU_CLOCK,
            GPU_FREE_MEM,
            GPU_USED_MEM,
            GPU_TEMP,
            GPU_WATT
        }

        static void Main()
        {
            Console.WriteLine("Thanks a lot for coming that far...");

            _commands.Clear();
            _commands.Add(Commands.CPU_MHZ_STR, "-c \"cat /proc/cpuinfo | grep 'MHz' | uniq | awk '{print $4}'\"");
            _commands.Add(Commands.RAM_STR, "-c \"free -m | awk '/^Mem/ {print $2/1000 \\\"\\n\\\" $3/1000}'\"");
           // _commands.Add(Commands.CPU_NAME,
            //    "-c \"lscpu | grep 'Model name' | awk -F ':' '{print $2}' | awk '{$1=$1};1'\"");
            //_commands.Add(Commands.GPU_NAME, "-c \"nvidia-smi --query-gpu=name --format=csv,noheader\"");
            _commands.Add(Commands.GPU_UTIL,
                "-c \"nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits\"");
            _commands.Add(Commands.GPU_CLOCK,
                "-c \"nvidia-smi --query-gpu=clocks.gr --format=csv,noheader,nounits\"");
            _commands.Add(Commands.GPU_FREE_MEM,
                "-c \"nvidia-smi --query-gpu=memory.free --format=csv,noheader,nounits\"");
            _commands.Add(Commands.GPU_USED_MEM,
                "-c \"nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits\"");
            _commands.Add(Commands.GPU_TEMP, "-c \"nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader\"");
            _commands.Add(Commands.GPU_WATT, "-c \"nvidia-smi --query-gpu=power.draw --format=csv,noheader,nounits\"");
            

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
                                try
                                {
                                    string file1 = Path.Combine(Directory.GetCurrentDirectory(), "turbostat_info1.txt");
                                    string trimCommand =
                                        $"-c \"tail -n 200 '{file}' > '{file1}' && mv '{file1}' '{file}' --force \"";
                                    //string trimCmd = $"-c \" echo \"$(tail -n 10 '{file}')\" > '{file}' \"";
                                    //string trimCommand = "echo \"$(tail -n 10 " + AddQuote() + file + AddQuote() + ") > " + AddQuote() + file + AddQuote();
                                    RunCommand("bash", trimCommand);
                                }
                                catch (Exception e)
                                {
                                    Console.WriteLine(e);
                                }

                                // Console.WriteLine("Stats File at: " + file);
                                string command =
                                    "turbostat --quiet --interval=0.2 --num_iterations=100 --show Busy%,PkgWatt,PkgTmp -out=" +
                                    AddQuote() + file + AddQuote();
                                _lastCpuUtilString =
                                    RunCommand("bash", "-c " + AddQuote() + command + AddQuote());
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
                    // if (!_cpuUtilThreadRunning)
                    // {
                    //     _cpuUtilThreadRunning = true;
                    //     Thread thread = new Thread(() =>
                    //     {
                    //         try
                    //         {
                    //             _lastCpuUtilString = RunCommand("bash", "-c \"mpstat -P ALL 1 1\"");
                    //         }
                    //         catch (Exception e)
                    //         {
                    //             Console.WriteLine(e);
                    //         }
                    //
                    //         _cpuUtilThreadRunning = false;
                    //     });
                    //     thread.Start();
                    // }

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

                    ConcurrentDictionary<Commands, string> _commandsOutput = GetSystemData(_commands);

                    // string gpuName = "";
                    // _commandsOutput.TryGetValue(Commands.GPU_NAME, out gpuName);
                    //
                    // string cpuName = "";
                    // _commandsOutput.TryGetValue(Commands.CPU_NAME, out cpuName);
                    //
                    // if (string.IsNullOrEmpty(cpuName) || string.IsNullOrEmpty(gpuName) ||
                    //     cpuName.ToLower().Contains("oem") || cpuName.ToLower().Contains("unknown"))
                    // {
                    //     continue;
                    // }

                    // _currentCPUName = cpuName;
                    // _currentGPUName = gpuName;

                    _dataToSend = CollectData(_commandsOutput);

                    // string file = Path.Combine(Directory.GetCurrentDirectory(), "turbostat_info.txt");
                    // // echo "$(tail -n 10 test.log)" > test.log
                    // string command = "echo \"$(tail -n 10 '" + file + "')\" > '" + file + "' ";
                    // RunCommand("bash", "-c \"" + command + "\"", true);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }

                Thread.Sleep(50);
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

                    Thread.Sleep(50);
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

        static ConcurrentDictionary<Commands, string> GetSystemData(Dictionary<Commands, string> commands)
        {

            var array = commands.ToArray();
            var commandOutput = new ConcurrentDictionary<Commands, string>();
            Parallel.ForEach(array, i =>
            {
                try
                {
                    string output = RunCommand("bash", i.Value);
                    commandOutput.TryAdd(i.Key, output);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e);
                }
            });
            return commandOutput;
        }


        static string CollectData(ConcurrentDictionary<Commands, string> CommandsOutput)
        {
            string data = "";

            string timeNow = $"Time_Now:{DateTime.Now.ToString("HH~mm")}:0:0:0|";
            data += timeNow;

            string dateNow = $"Date_Now:{DateTime.Now.ToShortDateString()}:0:0:0|";
            data += dateNow;

            //CollectCpuLoadAndClockData(ref data, CommandsOutput);
            CollectCpuData(ref data, CommandsOutput);

            CollectMemoryData(ref data, CommandsOutput);

            CollectStorageData(ref data);

            CollectNetworkData(ref data);

            CollectGpuData(ref data, CommandsOutput);

            // Very Important to send a char on the end of the message to allow the client to detect when the message ends
            data += "!";

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

        public static void CollectMemoryData(ref string properties,
            ConcurrentDictionary<Commands, string> _commandsOutput)
        {
            // string ramString = RunCommand("bash", "-c \"free -m | awk '/^Mem/ {print $2/1000 \\\"\\n\\\" $3/1000}'\"");
            string ramString = "";
            _commandsOutput.TryGetValue(Commands.RAM_STR, out ramString);
            // Console.WriteLine(ramString);

            if (ramString == null)
            {
                ramString = "";
            }

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

        public static void CollectCpuData(ref string properties, ConcurrentDictionary<Commands, string> _commandsOutput)
        {
            string name = _currentCPUName;
           //_commandsOutput.TryGetValue(Commands.CPU_NAME, out name);
            string file = Path.Combine(Directory.GetCurrentDirectory(), "turbostat_info.txt");
            // string wattageString = RunCommand("bash", $"-c \"cat \"{file}\"");
            // string tempString = RunSudoCommand("bash", "-c \"sudo turbostat --quiet --show PkgTmp 1 1\"");

            float pkgTmp = 0.0f;
            float pkgWatt = 0.0f;

            bool foundTmp = false;

            string[] stat_file = File.ReadAllLines(file);
            if (stat_file.Length > 0)
            {
                for (int idx = stat_file.Length - 1; idx >= 0; idx--)
                {
                    string[] info_lines = stat_file[idx].Trim()
                        .Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);

                    float dummy = 0;
                    // We are at the description of the values
                    if (!float.TryParse(info_lines[0].Replace(',', '.'), out dummy) && idx < stat_file.Length - 1)
                    {
                        string[] info_lines_overall = stat_file[idx + 1].Trim()
                            .Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);

                        for (int col = 0; col < info_lines.Length; col++)
                        {
                            if (info_lines[col].ToLower().Contains("pkgtmp"))
                            {
                                float tmp = 0.0f;
                                float.TryParse(info_lines_overall[col].Replace(',', '.'), out tmp);
                                if (tmp == 0.0f)
                                {
                                    pkgTmp = _currentCpuTemp;
                                    foundTmp = true;
                                }
                                else
                                {
                                    pkgTmp = tmp;
                                    _currentCpuTemp = tmp;
                                    foundTmp = true;
                                }
                            }

                            if (info_lines[col].ToLower().Contains("pkgwatt"))
                            {
                                float watt = 0.0f;
                                float.TryParse(info_lines_overall[col].Replace(',', '.'), out watt);
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


                            if (info_lines[col].ToLower().Contains("busy"))
                            {
                                float avg = 0.0f;
                                float.TryParse(info_lines_overall[col].Replace(',', '.'), out avg);

                                string avgLine = $"Cpu_Utility:Total:{avg}:0:100|";
                                properties += avgLine;

                                int threadIndex = 0;
                                for (int threadIdx = idx + 2; threadIdx < stat_file.Length; threadIdx++)
                                {
                                    string[] info_lines_thread = stat_file[threadIdx].Trim()
                                        .Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);

                                    if (info_lines_thread[col].ToLower().Contains("busy"))
                                    {
                                        break;
                                    }

                                    if (info_lines_thread.Length > col)
                                    {
                                        float threadLoad = 0.0f;
                                        float.TryParse(info_lines_thread[col].Replace(',', '.'), out threadLoad);

                                        string line = $"Cpu_Utility:{threadIndex}:{threadLoad}:0:100|";
                                        properties += line;
                                    }
                                    threadIndex++;
                                }
                            }
                        }

                        break;
                    }
                }
            }

            if (!foundTmp)
            {
                string sensors = RunCommand("bash", "-c \"sensors\"");

                string[] sensorLines = sensors.Split(new[] { Environment.NewLine },
                    StringSplitOptions.RemoveEmptyEntries);

                if (sensorLines.Length > 0)
                {
                    bool found = false;
                    float tmp = 0.0f;
                    for (int i = 0; i < sensorLines.Length; i++)
                    {
                        if (sensorLines[i].Contains("k10temp"))
                        {
                            found = true;
                        }

                        if (found && (sensorLines[i].ToLower().Contains("tctl") ||
                                      sensorLines[i].ToLower().Contains("tdie")))
                        {
                            string pattern = @"\d+\.\d+";
                            MatchCollection matches = Regex.Matches(sensorLines[i], pattern);

                            if (matches.Count > 0)
                            {
                                float.TryParse(matches[0].Value.Replace(',', '.'), out tmp);
                            }

                            break;
                        }
                    }

                    if (tmp == 0.0f)
                    {
                        pkgTmp = _currentCpuTemp;
                        foundTmp = true;
                    }
                    else
                    {
                        pkgTmp = tmp;
                        _currentCpuTemp = tmp;
                        foundTmp = true;
                    }
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

            // string mhzString = RunCommand("bash", "-c \"cat /proc/cpuinfo | grep 'MHz' | uniq | awk '{print $4}'\"");
            string mhzString = "";
            _commandsOutput.TryGetValue(Commands.CPU_MHZ_STR, out mhzString);

            if (mhzString == null)
            {
                mhzString = "";
            }

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

        public static void CollectGpuData(ref string properties, ConcurrentDictionary<Commands, string> _commandsOutput)
        {
            // string name = RunCommand("bash", "-c \"nvidia-smi --query-gpu=name --format=csv,noheader\"");
            // string utility = RunCommand("bash",
            //     "-c \"nvidia-smi --query-gpu=utilization.gpu --format=csv,noheader,nounits\"");
            // string clock = RunCommand("bash", "-c \"nvidia-smi --query-gpu=clocks.gr --format=csv,noheader,nounits\"");
            // string freeMem = RunCommand("bash",
            //     "-c \"nvidia-smi --query-gpu=memory.free --format=csv,noheader,nounits\"");
            // string usedMem = RunCommand("bash",
            //     "-c \"nvidia-smi --query-gpu=memory.used --format=csv,noheader,nounits\"");
            // string temp = RunCommand("bash", "-c \"nvidia-smi --query-gpu=temperature.gpu --format=csv,noheader\"");
            // string watt = RunCommand("bash", "-c \"nvidia-smi --query-gpu=power.draw --format=csv,noheader,nounits\"");
            string name = _currentGPUName;
           // _commandsOutput.TryGetValue(Commands.GPU_NAME, out name);
            string utility = "";
            _commandsOutput.TryGetValue(Commands.GPU_UTIL, out utility);
            string clock = "";
            _commandsOutput.TryGetValue(Commands.GPU_CLOCK, out clock);
            string freeMem = "";
            _commandsOutput.TryGetValue(Commands.GPU_FREE_MEM, out freeMem);
            string usedMem = "";
            _commandsOutput.TryGetValue(Commands.GPU_USED_MEM, out usedMem);
            string temp = "";
            _commandsOutput.TryGetValue(Commands.GPU_TEMP, out temp);
            string watt = "";
            _commandsOutput.TryGetValue(Commands.GPU_WATT, out watt);

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