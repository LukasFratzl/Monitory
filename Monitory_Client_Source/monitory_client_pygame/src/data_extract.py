from src.frame_dirty import *

# Example data LINUX:
# Received: Time_Now:00~39:0:0:0|Date_Now:25/05/2026:0:0:0|Cpu_Utility:Total:2.08:0:100|Cpu_Utility:0:7.0:0:100|Cpu_Utility:1:0.07:0:100|Cpu_Utility:2:1.14:0:100|Cpu_Utility:3:1.23:0:100|Cpu_Utility:4:0.85:0:100|Cpu_Utility:5:0.06:0:100|Cpu_Utility:6:0.05:0:100|Cpu_Utility:7:2.2:0:100|Cpu_Utility:8:0.03:0:100|Cpu_Utility:9:5.07:0:100|Cpu_Utility:10:1.69:0:100|Cpu_Utility:11:5.52:0:100|Cpu_Utility:12:0.01:0:100|Cpu_Utility:13:0.67:0:100|Cpu_Utility:14:0.18:0:100|Cpu_Utility:15:0.01:0:100|Cpu_Utility:16:2.04:0:100|Cpu_Utility:17:0.01:0:100|Cpu_Utility:18:16.93:0:100|Cpu_Utility:19:0.49:0:100|Cpu_Utility:20:1.64:0:100|Cpu_Utility:21:0.12:0:100|Cpu_Utility:22:1.1:0:100|Cpu_Utility:23:1.72:0:100|Cpu_Utility:24:1.62:0:100|Cpu_Utility:25:5.99:0:100|Cpu_Utility:26:0.5:0:100|Cpu_Utility:27:5.24:0:100|Cpu_Utility:28:0.01:0:100|Cpu_Utility:29:1.65:0:100|Cpu_Utility:30:0.16:0:100|Cpu_Utility:31:1.61:0:100|Cpu_Clock:Total:4670.8603370361325:0:100|Cpu_Clock:0:5168.848:0:100|Cpu_Clock:1:5676.124:0:100|Cpu_Clock:2:5666.39:0:100|Cpu_Clock:3:5686.512:0:100|Cpu_Clock:4:5681.359:0:100|Cpu_Clock:5:624.194:0:100|Cpu_Clock:6:4047.763:0:100|Cpu_Clock:7:624.194:0:100|Cpu_Clock:8:4045.435:0:100|Cpu_Clock:9:5476.618:0:100|Cpu_Clock:10:5458.642:0:100|Cpu_Clock:11:624.194:0:100|Cpu_Clock:12:5475.87:0:100|Cpu_Clock:13:624.194:0:100|Cpu_Clock:14:5464.798:0:100|Cpu_Clock:15:624.194:0:100|Cpu_Clock:16:5458.664:0:100|Cpu_Clock:17:5477.297:0:100|Cpu_Clock:18:None:0:100|Cpu_Clock:19:None:0:100|Cpu_Clock:20:None:0:100|Cpu_Clock:21:None:0:100|Cpu_Clock:22:None:0:100|Cpu_Clock:23:None:0:100|Cpu_Clock:24:None:0:100|Cpu_Clock:25:None:0:100|Cpu_Clock:26:None:0:100|Cpu_Clock:27:None:0:100|Cpu_Clock:28:None:0:100|Cpu_Clock:29:None:0:100|Cpu_Clock:30:None:0:100|Cpu_Clock:31:None:0:100|Wattage:Compute Unit:55.55:0:100|Temperature:Compute Unit:50.9:0:100|Cpu_Memory:Used:5.204:0:100|Cpu_Memory:Available:88.98200000000001:0:100|Storage_Load:sdb:0.0:0:100|Storage_Load:sda:0.0:0:100|Storage_Load:nvme1n1:0.3:0:100|Storage_Load:nvme0n1:0.0:0:100|Storage_Load:loop9:0.0:0:100|Storage_Load:loop8:0.0:0:100|Storage_Load:loop7:0.0:0:100|Storage_Load:loop6:0.0:0:100|Storage_Load:loop5:0.0:0:100|Storage_Load:loop4:0.0:0:100|Storage_Load:loop3:0.0:0:100|Storage_Load:loop2:0.0:0:100|Storage_Load:loop16:0.0:0:100|Storage_Load:loop15:0.0:0:100|Storage_Load:loop14:0.0:0:100|Storage_Load:loop13:0.0:0:100|Storage_Load:loop12:0.0:0:100|Storage_Load:loop11:0.0:0:100|Storage_Load:loop10:0.0:0:100|Storage_Load:loop1:0.0:0:100|Storage_Load:loop0:0.0:0:100|Storage_Load:dm-2:0.0:0:100|Storage_Load:dm-1:0.3:0:100|Storage_Load:dm-0:0.3:0:100|Upload_Speed:Total:15831.04:15831.04:0|Download_Speed:Total:2263.04:2263.04:0|Gpu_Utility:Clock:72.0:0:100|Gpu_Clock:Clock:315.0:0:100|Gpu_Memory:Available:23.716:0:100|Gpu_Memory:Used:0.346:0:100|Wattage:Graphics:20.84:0:100|Temperature:Graphics:47.0:0:100|

# Example data WIN:
# WIN DATA: Cpu_Utility:0:19,425386:5,0609055:73,71152|Cpu_Utility:1:10,771805:2,4868965:39,84945|Cpu_Utility:2:49,50784:3,9684951:75,10016|Cpu_Utility:3:18,134647:3,8236082:58,57522|Cpu_Utility:4:6,4947186:0,96425414:38,228996|Cpu_Utility:5:6,5119624:0:37,202816|Cpu_Utility:6:9,574223:1,7502844:80,38368|Cpu_Utility:7:6,4362645:0,7909298:55,3824|Cpu_Utility:8:5,7453156:0:36,67875|Cpu_Utility:9:4,1501164:0:34,285122|Cpu_Utility:10:40,256073:1,9671082:72,1021|Cpu_Utility:11:35,20103:5,0692616:70,05281|Cpu_Utility:12:4,8461494:0:32,1601|Cpu_Utility:13:3,229016:0:31,65139|Cpu_Utility:14:3,1475902:0:33,83718|Cpu_Utility:15:2,6461184:0:37,220383|Cpu_Utility:16:4,5276823:0:28,62799|Cpu_Utility:17:2,5321245:0:29,527557|Cpu_Utility:18:2,883166:0:30,016088|Cpu_Utility:19:3,0220091:0:29,475807|Cpu_Utility:20:1,9172966:0:17,701763|Cpu_Utility:21:2,2373676:0:21,35821|Cpu_Utility:22:3,9152026:0:18,843794|Cpu_Utility:23:2,1359265:0:25,850178|Cpu_Utility:24:2,2610843:0:27,719616|Cpu_Utility:25:4,02258:0:24,628056|Cpu_Utility:26:2,1820426:0:29,29786|Cpu_Utility:27:2,052766:0:41,302544|Cpu_Utility:28:2,0369768:0:16,794527|Cpu_Utility:29:3,7741482:0:19,990683|Cpu_Utility:30:4,465848:0:73,45805|Cpu_Utility:31:2,0478606:0:80,56235|Cpu_Utility:Total:8,502883:3,0225396:32,653076|Cpu_Utility:32:49,50784:36,666428:80,56235|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Clock:0:NaN:NaN:NaN|Cpu_Memory:Used:44,966663:44,88756:44,997265|Cpu_Memory:Available:48,6924:48,6618:48,771503|Gpu_Memory:Available:2,0135233:2,0135233:2,0135233|Gpu_Memory:Used:0,008242187:0,008242187:0,008242187|Gpu_Memory:Used:0,017316407:0,017316407:0,017316407|Gpu_Memory:Available:47,936127:47,936127:47,936127|Gpu_Memory:Used:0,008:0,008:0,008|Gpu_Memory:Available:2,04:2,04:2,04|Gpu_Clock:Clock:600:600:600|Gpu_Utility:Clock:0:0:0|Gpu_Clock:Clock:210:210:255|Gpu_Utility:Clock:14:2:38|Gpu_Memory:Used:2,3962617:2,386879:2,3962617|Gpu_Memory:Used:0,17601563:0,17409375:0,17732422|Gpu_Memory:Available:21,75:21,75:21,759|Gpu_Memory:Used:2,813:2,804:2,813|Cpu_Clock:Total:5160:-1:5289|Wattage:AMD Ryzen 9 9950X:0:0:0|Wattage:AMD Radeon(TM) Graphics:12:11:64|Wattage:NVIDIA GeForce RTX 4090:17,832:14,175:19,165|Temperature:AMD Ryzen 9 9950X:0:0:0|Temperature:AMD Radeon(TM) Graphics:49:48:50|Temperature:NVIDIA GeForce RTX 4090:49:48:49|Time_Now:21~07:0:0:0|Date_Now:30/05/2026:0:0:0|Download_Speed:Bluetooth Network Connection:0:0:0|Download_Speed:Local Area Connection* 10:0:0:0|Download_Speed:Local Area Connection* 9:0:0:0|Download_Speed:OpenVPN Data Channel Offload for Surfshark:0:0:0|Download_Speed:Wi-Fi 3:7417,1245:0:22936,672|Upload_Speed:Bluetooth Network Connection:0:0:0|Upload_Speed:Local Area Connection* 10:0:0:0|Upload_Speed:Local Area Connection* 9:0:0:0|Upload_Speed:OpenVPN Data Channel Offload for Surfshark:0:0:0|Upload_Speed:Wi-Fi 3:99670,055:0:134098,89|Dark_Mode:0:1:0:0|!


export_stats_json =	{"Time_Now": "",
			"Date_Now": "",
			"Cpu_Utility_Total": 0,
			"Cpu_Utility_Thread": [],
			"Cpu_Utility_Thread_fallback": [],
			"Cpu_Clock_Average": 0,
			"Cpu_Clock_Thread": [],
			"Cpu_Clock_Thread_fallback": [],
			"Wattage": {},
			"Wattage_fallback": {},
			"Temperature": {},
			"Temperature_fallback": {},
			"Cpu_Memory_Available": 0,
			"Cpu_Memory_Used": 0,
			"Storage_Load": {},
			"Storage_Load_fallback": {},
			"Net_Upload_Speed": 0,
			"Net_Download_Speed": 0,
			"Gpu_Utility": 0,
			"Gpu_Clock": 0,
			"Gpu_Memory_Available": 0,
			"Gpu_Memory_Used": 0}
			
def translate_data(raw_string):

    base_data = raw_string.split('!')
    data = base_data[0].split('|')
    
    # Test the data
    data_valid = False
    for item in data:
        slices = item.split(":")
        if len(slices) != 5:
            continue
            
        label = slices[0]
        sub_label = slices[1]  
            
        if "Cpu_Utility" in label:
            data_valid = True
            break
        
    # This check prevents the missing pieces in the graph
    # because the send data is slower as the app FPS
    if not data_valid:
        return
        
    set_frame_dirty(True)
        
    export_stats_json["Cpu_Utility_Thread"] = []
    export_stats_json["Cpu_Clock_Thread"] = []
    export_stats_json["Storage_Load"] = dict()
    export_stats_json["Wattage"] = dict()
    export_stats_json["Temperature"] = dict()
    
    for item in data:
        slices = item.split(":")
        if len(slices) != 5:
            continue
        
        label = slices[0]
        sub_label = slices[1]
        
        try:
            current_val = float(slices[2].replace(",", "."))
        except:
            current_val = 0.0
            
        try:
            min_val = float(slices[3].replace(",", "."))
        except:
            min_val = 0.0
        
        try:
            max_val = float(slices[4].replace(",", "."))
        except:
            max_val = 0.0
        
        
        
        if "Time_Now" in label:
            time_now = sub_label.split('~')
            export_stats_json["Time_Now"] = time_now[0] + ":" + time_now[1]
        
        if "Date_Now" in label:
            export_stats_json["Date_Now"] = sub_label
            
        if "Cpu_Utility" in label:
            if "Total" in sub_label:
                export_stats_json["Cpu_Utility_Total"] = current_val * 0.01
            else:
                export_stats_json["Cpu_Utility_Thread"].append(current_val * 0.01)
            
        if "Cpu_Clock" in label:
            if "Total" in sub_label:
                export_stats_json["Cpu_Clock_Average"] = current_val
            else:
                export_stats_json["Cpu_Clock_Thread"].append(current_val)
                
        if "Wattage" in label:
            export_stats_json["Wattage"][sub_label] = current_val
                
        if "Temperature" in label:
            export_stats_json["Temperature"][sub_label] = current_val
                
        if "Cpu_Memory" in label:
            if "Used" in sub_label:
                export_stats_json["Cpu_Memory_Used"] = current_val
            if "Available" in sub_label:
                export_stats_json["Cpu_Memory_Available"] = current_val
                
        if "Storage_Load" in label:
            export_stats_json["Storage_Load"][sub_label] = current_val
            
        if "Upload_Speed" in label:
            export_stats_json["Net_Upload_Speed"] = current_val
            
        if "Download_Speed" in label:
            export_stats_json["Net_Download_Speed"] = current_val
            
        if "Gpu_Utility" in label:
            export_stats_json["Gpu_Utility"] = current_val * 0.01
            
        if "Gpu_Clock" in label:
            export_stats_json["Gpu_Clock"] = current_val
            
        if "Gpu_Memory" in label:
            if "Used" in sub_label:
                export_stats_json["Gpu_Memory_Used"] = current_val
            if "Available" in sub_label:
                export_stats_json["Gpu_Memory_Available"] = current_val
            
    if len(export_stats_json["Cpu_Utility_Thread"]) < 1:
        export_stats_json["Cpu_Utility_Thread"] = export_stats_json["Cpu_Utility_Thread_fallback"].copy()
    else:
        export_stats_json["Cpu_Utility_Thread_fallback"] = export_stats_json["Cpu_Utility_Thread"].copy()
        
    if len(export_stats_json["Cpu_Clock_Thread"]) < 1:
        export_stats_json["Cpu_Clock_Thread"] = export_stats_json["Cpu_Clock_Thread_fallback"].copy()
    else:
        export_stats_json["Cpu_Clock_Thread_fallback"] = export_stats_json["Cpu_Clock_Thread"].copy()
        
    if len(export_stats_json["Storage_Load"]) < 1:
        export_stats_json["Storage_Load"] = export_stats_json["Storage_Load_fallback"].copy()
    else:
        export_stats_json["Storage_Load_fallback"] = export_stats_json["Storage_Load"].copy()
        
    if len(export_stats_json["Wattage"]) < 1:
        export_stats_json["Wattage"] = export_stats_json["Wattage_fallback"].copy()
    else:
        export_stats_json["Wattage_fallback"] = export_stats_json["Wattage"].copy()
        
    if len(export_stats_json["Temperature"]) < 1:
        export_stats_json["Temperature"] = export_stats_json["Temperature_fallback"].copy()
    else:
        export_stats_json["Temperature_fallback"] = export_stats_json["Temperature"].copy()
