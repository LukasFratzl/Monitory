using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Numerics;
using System.Text;
using LibreHardwareMonitor.Hardware;

namespace Monitory_Server_Windows
{
	class ScheduledTask
	{
		internal readonly Action Action;
		internal System.Timers.Timer Timer;
		internal EventHandler TaskComplete;

		public ScheduledTask(Action action, int timeoutMs)
		{
			Action = action;
			Timer = new System.Timers.Timer() { Interval = timeoutMs };
			Timer.Elapsed += TimerElapsed;
		}

		private void TimerElapsed(object sender, System.Timers.ElapsedEventArgs e)
		{
			Timer.Stop();
			Timer.Elapsed -= TimerElapsed;
			Timer = null;

			Action();
			TaskComplete(this, EventArgs.Empty);
		}
	}

	class Program
	{
		private static List<ScheduledTask> _scheduledTasks = new List<ScheduledTask>();

		private const string TotalName = "total";
		private const string CoreName = "core";
		private const string ThreadName = "thread";
		private const string UsedName = "used";
		private const string AvailableName = "available";
		private const string FreeName = "free";
		private const string VirtualName = "virtual";
		private const string TjName = "tj";
		private const string HotSpotName = "hot";
		private const string DownloadName = "down";
		private const string UploadName = "up";

		static string _dataToSend = "";

		private class UpdateVisitor : IVisitor
		{
			public void VisitComputer(IComputer computer)
			{
				computer.Traverse(this);
			}
			public void VisitHardware(IHardware hardware)
			{
				hardware.Update();
				foreach (IHardware subHardware in hardware.SubHardware) subHardware.Accept(this);
			}
			public void VisitSensor(ISensor sensor) { }
			public void VisitParameter(IParameter parameter) { }
		}

		private static Computer _computer = new Computer();

		private readonly TcpListener _server = new TcpListener(IPAddress.Any, 54000);

		private static void Main()
		{

			Console.WriteLine("Thanks a lot for coming that far...");
			Console.WriteLine("Make sure to run the app as admin, otherwise some monitor fetures are not available...");

			bool bRunning = true;
			
			bool bInit = true;
			while (bRunning)
			{
				try
				{
					_scheduledTasks = MainLoop(bInit);
					bInit = false;
				}
				catch (Exception e)
				{
					Console.WriteLine(e);

					Thread.Sleep(500);
				}
			}
		}

		private void server_start()
		{
			_server.Start();
			accept_connection();  //accepts incoming connections
		}

		private void accept_connection()
		{
			_server.BeginAcceptTcpClient(handle_connection, _server);  //this is called asynchronously and will run in a different thread
		}

		private void handle_connection(IAsyncResult result)  //the parameter is a delegate, used to communicate between threads
		{
			accept_connection();  //once again, checking for any other incoming connections
			TcpClient client = _server.EndAcceptTcpClient(result);  //creates the TcpClient

			NetworkStream ns = client.GetStream();

			/* here you can add the code to send/receive data */

			Console.WriteLine("Client Connected");

			try
			{
				while (client.Connected)  //while the client is connected, we look for incoming messages
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
			} finally {
				client.Dispose();
				client.Close();
				ns.Dispose();
				ns.Close();
			}

		}

		static List<ScheduledTask> MainLoop(bool bIsInit)
		{
			_computer = new Computer
			{
				IsCpuEnabled = true,
				IsGpuEnabled = true,
				IsMemoryEnabled = true,
				IsMotherboardEnabled = true,
				IsControllerEnabled = true,
				IsNetworkEnabled = true,
				IsStorageEnabled = true
			};

			var tasks = new List<ScheduledTask>();

			_computer.Open();
			_computer.Accept(new UpdateVisitor());

			if (bIsInit)
			{
				foreach (IHardware hardware in _computer.Hardware)
				{
					Console.WriteLine("Hardware Type: {0}", hardware.HardwareType);
					Console.WriteLine("Hardware: {0}", hardware.Name);

					foreach (IHardware subhardware in hardware.SubHardware)
					{
						Console.WriteLine("\tSubhardware Type: {0}", subhardware.HardwareType);
						Console.WriteLine("\tSubhardware: {0}", subhardware.Name);

						foreach (ISensor sensor in subhardware.Sensors)
						{
							Console.WriteLine("\t\tSensor: {0}, Type: {1}, Value: {2}", sensor.Name, sensor.SensorType,
								sensor.Value);
						}
					}

					foreach (ISensor sensor in hardware.Sensors)
					{
						Console.WriteLine("\tSensor: {0}, Type: {1}, Value: {2}", sensor.Name, sensor.SensorType,
							sensor.Value);
					}
				}	
			}

			if (bIsInit)
			{
				try
				{
					var syncTimer1 = new ScheduledTask(() => RunW32tmResync(), 120000);
					tasks.Add(syncTimer1);
					syncTimer1.Timer.Start();

					var syncTimer2 = new ScheduledTask(() => RunW32tmResync(), 600000);
					tasks.Add(syncTimer2);
					syncTimer2.Timer.Start();

					var syncTimer3 = new ScheduledTask(() => RunW32tmResync(), 1200000);
					tasks.Add(syncTimer3);
					syncTimer3.Timer.Start();
				}
				catch (Exception e)
				{
					Console.WriteLine(e);
				}
			}

			bool bNeedExit = false;

			Program main = new Program();
			main.server_start(); //starting the server

			while (!bNeedExit)
			{
				_dataToSend = CollectData();
				Thread.Sleep(300);
			}

			Console.WriteLine("Press any key to exit...");

			// Wait for a key press
			Console.ReadKey();

			Console.WriteLine("Exiting the program.");

			_computer.Close();

			return tasks;
		}

		static string CollectData()
		{
			int threadLoadIndex = 0;
			int threadClockIndex = 0;
			Vector3 clockSpeedTotal = new Vector3(-1f, -1f, -1f);
			Dictionary<string, Vector3> watts = new Dictionary<string, Vector3>();
			Dictionary<string, Vector3> temps = new Dictionary<string, Vector3>();
			Dictionary<string, Vector3> downloadSpeeds = new Dictionary<string, Vector3>();
			Dictionary<string, Vector3> uploadSpeeds = new Dictionary<string, Vector3>();

			string properties = "";
			_computer.Accept(new UpdateVisitor());

			foreach (IHardware hardware in _computer.Hardware)
			{
				foreach (IHardware subhardware in hardware.SubHardware)
				{
					foreach (ISensor sensor in subhardware.Sensors)
					{
						if (subhardware.HardwareType == HardwareType.Cpu ||
						    subhardware.HardwareType == HardwareType.GpuNvidia ||
						    subhardware.HardwareType == HardwareType.GpuIntel ||
						    subhardware.HardwareType == HardwareType.GpuAmd)
						{
							CollectPowerData(sensor, subhardware.Name, ref watts);
							CollectTemperatureData(sensor, subhardware.Name, ref temps);
						}

						if (hardware.HardwareType == HardwareType.Cpu)
						{
							CollectCpuLoadAndClockData(sensor, ref threadLoadIndex, ref threadClockIndex, ref clockSpeedTotal, ref properties);
						}
						CollectMemoryData(sensor, ref properties);
						CollectGpuData(sensor, ref properties);
						if (hardware.HardwareType == HardwareType.Storage)
						{
							CollectStorageData(sensor, ref properties);
						}
						if (hardware.HardwareType == HardwareType.Network)
						{
							CollectNetworkData(sensor, hardware.Name, ref properties, ref downloadSpeeds, ref uploadSpeeds);
						}
					}
				}

				foreach (ISensor sensor in hardware.Sensors)
				{
					if (hardware.HardwareType == HardwareType.Cpu ||
					    hardware.HardwareType == HardwareType.GpuNvidia ||
					    hardware.HardwareType == HardwareType.GpuIntel ||
					    hardware.HardwareType == HardwareType.GpuAmd)
					{
						CollectPowerData(sensor, hardware.Name, ref watts);
						CollectTemperatureData(sensor, hardware.Name, ref temps);
					}
					if (hardware.HardwareType == HardwareType.Cpu)
					{
						CollectCpuLoadAndClockData(sensor, ref threadLoadIndex, ref threadClockIndex, ref clockSpeedTotal, ref properties);
					}
					CollectMemoryData(sensor, ref properties);
					CollectGpuData(sensor, ref properties);
					if (hardware.HardwareType == HardwareType.Storage)
					{
						CollectStorageData(sensor, ref properties);
					}
					if (hardware.HardwareType == HardwareType.Network)
					{
						CollectNetworkData(sensor, hardware.Name, ref properties, ref downloadSpeeds, ref uploadSpeeds);
					}
				}
			}

			// Capture and write the total CPU load to the file
			string cpuClockTotal = $"Cpu_Clock:Total:{clockSpeedTotal.X}:{clockSpeedTotal.Y}:{clockSpeedTotal.Z}|";
			properties += cpuClockTotal;

			foreach (var powerValue in watts) {
				string power = $"Wattage:{powerValue.Key}:{powerValue.Value.X}:{powerValue.Value.Y}:{powerValue.Value.Z}|";
				properties += power;
			}

			foreach (var tempValue in temps)
			{
				string temp = $"Temperature:{tempValue.Key}:{tempValue.Value.X}:{tempValue.Value.Y}:{tempValue.Value.Z}|";
				properties += temp;
			}

			string timeNow = $"Time_Now:{DateTime.Now.ToString("HH~mm")}:0:0:0|";
			properties += timeNow;

			string dateNow = $"Date_Now:{DateTime.Now.ToShortDateString()}:0:0:0|";
			properties += dateNow;

			foreach (var downValue in downloadSpeeds)
			{
				string download = $"Download_Speed:{downValue.Key}:{downValue.Value.X}:{downValue.Value.Y}:{downValue.Value.Z}|";
				properties += download;
			}

			foreach (var uploadValue in uploadSpeeds)
			{
				string upload = $"Upload_Speed:{uploadValue.Key}:{uploadValue.Value.X}:{uploadValue.Value.Y}:{uploadValue.Value.Z}|";
				properties += upload;
			}

			return properties;
		}

		public static void CollectPowerData(ISensor sensor, string hardwareName, ref Dictionary<string, Vector3> watts)
		{
			if (sensor.SensorType == SensorType.Power)
			{
				watts.TryAdd(hardwareName, new Vector3());

				Vector3 power = watts[hardwareName];

				power.X = MathF.Max(power.X, sensor.Value.GetValueOrDefault());

				if (power.Y <= 0)
				{
					power.Y = sensor.Min.GetValueOrDefault();
				}
				else
				{
					power.Y = MathF.Min(power.Y, sensor.Min.GetValueOrDefault());
				}

				if (power.Z <= 0)
				{
					power.Z = sensor.Max.GetValueOrDefault();
				}
				else
				{
					power.Z = MathF.Max(power.Z, sensor.Max.GetValueOrDefault());
				}

				watts[hardwareName] = power;
			}

			//return watts;
		}

		public static void CollectCpuLoadAndClockData(ISensor sensor, ref int threadLoadIndex, ref int threadClockIndex, ref Vector3 clockSpeedTotal, ref string properties)
		{
			string sensorName = sensor.Name.ToLower();
			if (sensor.SensorType == SensorType.Load)
			{
				if (sensorName.Contains(TotalName) || (!sensorName.Contains(CoreName) && !sensorName.Contains(ThreadName)))
				{
					string line = $"Cpu_Utility:Total:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}
				else
				{
					string line = $"Cpu_Utility:{threadLoadIndex}:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;

					threadLoadIndex++;
				}
			}

			if (sensor.SensorType == SensorType.Clock && (sensorName.Contains(CoreName) || sensorName.Contains(ThreadName)))
			{
				string line = $"Cpu_Clock:{threadClockIndex}:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
				properties += line;

				threadLoadIndex++;

				if (clockSpeedTotal.X <= 0)
				{
					clockSpeedTotal.X = sensor.Value.GetValueOrDefault();
				}
				else
				{
					clockSpeedTotal.X = (clockSpeedTotal.X + sensor.Value.GetValueOrDefault()) / 2;
				}

				if (clockSpeedTotal.Y <= 0)
				{
					clockSpeedTotal.Y = sensor.Min.GetValueOrDefault();
				}
				else
				{
					clockSpeedTotal.Y = MathF.Min(clockSpeedTotal.Y, sensor.Min.GetValueOrDefault());
				}

				if (clockSpeedTotal.Z <= 0)
				{
					clockSpeedTotal.Z = sensor.Max.GetValueOrDefault();
				}
				else
				{
					clockSpeedTotal.Z = MathF.Max(clockSpeedTotal.Z, sensor.Max.GetValueOrDefault());
				}
			}
		}

		public static void CollectMemoryData(ISensor sensor, ref string properties)
		{
			if (sensor.SensorType == SensorType.Data)
			{
				string sensorName = sensor.Name.ToLower();
				if ((sensorName.Contains(AvailableName) || sensorName.Contains(FreeName)) && !sensorName.Contains(VirtualName))
				{
					string line = $"Cpu_Memory:Available:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}

				if (sensorName.Contains(UsedName) && !sensorName.Contains(VirtualName))
				{
					string line = $"Cpu_Memory:Used:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}
			}
		}

		public static void CollectGpuData(ISensor sensor, ref string properties)
		{
			string sensorName = sensor.Name.ToLower();
			if (sensor.SensorType == SensorType.Clock)
			{
				if (sensorName.Contains(CoreName))
				{
					string line = $"Gpu_Clock:Clock:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}
			}

			if (sensor.SensorType == SensorType.Load)
			{
				if (sensorName.Contains(CoreName))
				{
					string line = $"Gpu_Utility:Clock:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}
			}

			if (sensor.SensorType == SensorType.Data || sensor.SensorType == SensorType.SmallData)
			{
				if (sensorName.Contains(FreeName) || sensorName.Contains(AvailableName))
				{
					string line = sensor.SensorType == SensorType.SmallData ? $"Gpu_Memory:Available:{sensor.Value / 1000}:{sensor.Min / 1000}:{sensor.Max / 1000}|" : $"Gpu_Memory:Available:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}

				if (sensorName.Contains(UsedName))
				{
					string line = sensor.SensorType == SensorType.SmallData ? $"Gpu_Memory:Used:{sensor.Value / 1000}:{sensor.Min / 1000}:{sensor.Max / 1000}|" : $"Gpu_Memory:Used:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += line;
				}
			}
		}

		public static void CollectTemperatureData(ISensor sensor, string hardwareName, ref Dictionary<string, Vector3> temps)
		{
			string sensorName = sensor.Name.ToLower();
			if (sensor.SensorType == SensorType.Temperature && !sensorName.Contains(TjName) && !sensorName.Contains(
				    HotSpotName))
			{
				temps.TryAdd(hardwareName, new Vector3());

				Vector3 temp = temps[hardwareName];

				if (temp.X < sensor.Value.GetValueOrDefault())
				{
					temp.X = sensor.Value.GetValueOrDefault();
				}

				if (temp.Y <= 0)
				{
					temp.Y = sensor.Min.GetValueOrDefault();
				}
				else
				{
					temp.Y = MathF.Min(temp.Y, sensor.Min.GetValueOrDefault());
				}

				if (temp.Z <= 0)
				{
					temp.Z = sensor.Max.GetValueOrDefault();
				}
				else
				{
					temp.Z = MathF.Max(temp.Z, sensor.Max.GetValueOrDefault());
				}

				temps[hardwareName] = temp;
			}
		}

		public static void CollectStorageData(ISensor sensor, ref string properties)
		{
			string sensorName = sensor.Name.ToLower();
			if (sensor.SensorType == SensorType.Load)
			{
				if (sensorName.Contains(TotalName))
				{
					string storage = $"Storage_Load:{sensor.Name}:{sensor.Value}:{sensor.Min}:{sensor.Max}|";
					properties += storage;
				}
			}
		}

		public static void CollectNetworkData(ISensor sensor, string hardwareName, ref string properties, ref Dictionary<string, Vector3> down, ref Dictionary<string, Vector3> up)
		{
			string sensorName = sensor.Name.ToLower();
			if (sensor.SensorType == SensorType.Throughput)
			{
				if (sensorName.Contains(DownloadName))
				{
					down.TryAdd(hardwareName, new Vector3());

					Vector3 value = down[hardwareName];

					if (value.X < sensor.Value.GetValueOrDefault())
					{
						value.X = sensor.Value.GetValueOrDefault();
					}

					if (value.Y <= 0)
					{
						value.Y = sensor.Min.GetValueOrDefault();
					}
					else
					{
						value.Y = MathF.Min(value.Y, sensor.Min.GetValueOrDefault());
					}

					if (value.Z <= 0)
					{
						value.Z = sensor.Max.GetValueOrDefault();
					}
					else
					{
						value.Z = MathF.Max(value.Z, sensor.Max.GetValueOrDefault());
					}

					down[hardwareName] = value;
				}

				if (sensorName.Contains(UploadName))
				{
					up.TryAdd(hardwareName, new Vector3());

					Vector3 value = up[hardwareName];

					if (value.X < sensor.Value.GetValueOrDefault())
					{
						value.X = sensor.Value.GetValueOrDefault();
					}

					if (value.Y <= 0)
					{
						value.Y = sensor.Min.GetValueOrDefault();
					}
					else
					{
						value.Y = MathF.Min(value.Y, sensor.Min.GetValueOrDefault());
					}

					if (value.Z <= 0)
					{
						value.Z = sensor.Max.GetValueOrDefault();
					}
					else
					{
						value.Z = MathF.Max(value.Z, sensor.Max.GetValueOrDefault());
					}

					up[hardwareName] = value;
				}
			}
		}


		public static void RunW32tmResync()
		{
			// Create a new process start info
			ProcessStartInfo processStartInfo = new ProcessStartInfo
			{
				FileName = "cmd.exe", // Specify the command prompt executable
				RedirectStandardInput = true,
				UseShellExecute = false,
				RedirectStandardOutput = true,
				CreateNoWindow = true
			};

			// Create a new process
			Process process = new Process { StartInfo = processStartInfo };

			// Start the process
			process.Start();

			// Execute the w32tm /resync command
			using (var sw = process.StandardInput)
			{
				if (sw.BaseStream.CanWrite)
				{
					sw.WriteLine("w32tm /resync");
				}
			}

			// Wait for the process to exit
			process.WaitForExit();

			// Display the output (optional)
			string output = process.StandardOutput.ReadToEnd();
			Console.WriteLine(output);

			// Close the process
			process.Close();
		}

	}
}