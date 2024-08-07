# Monitory

*_Monitory is a Cross-Platform Monitoring App which allows to Monitor a Linux or Windows Device through a Android Phone or Tablet_*

## Server:
*_Monitory Server Apps are available for Windows and Linux, this apps reading the hardware and sending it via TCP to the Clients_*
#### Windows:
 - Navigate to the Releases and download a Windows Server version
 - It's good practice to Run the App as Admin
 - When you like the app and want keep it running every Windows Start, create an automated Task <https://www.windowscentral.com/how-create-automated-tasks-windows-11>

#### Linux:
 - Navigate to the Releases and download a Linux Server version
 - Make sure you have `mpstat` `iostat` `ifstat` `cat` `nvidia-smi` installed
 - Only NVIDIA GPUs are supported for Linux
 - Run it and when you like it add it as start up application

## Client:
*_Monitory Client Apps are available for Android, this apps reading the TCP Data sended from the Monitory Server App to display the Hardware Infos on this Client Device_*
 ![Client App](Docs/Monitory_Client_1.gif)
#### Android:
 - Navigate to the Releases and download an Android Client version
 - Install it on your Android Device, it needs to be 64 Bit, Android 8 or Higher, ES3.1 or Higher
 - Run it and Play with the customization settings
 - White List the Server IP, you can have multiple Servers and it should connect with the Server

## Development:
 - Server Applications are writtent in c# .NET, open the solution and build it
 - Client Application is written in Unreal Engine 5 C++, you need to have UE 5.4.3 Installed and you need to own a copy of [UMG Spline](https://www.unrealengine.com/marketplace/en-US/product/umgspline) to install it to the Engine, In future I probably will replace UMG Spline with my own implmentation to stay independent...
