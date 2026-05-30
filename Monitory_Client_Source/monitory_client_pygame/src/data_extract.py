from src.frame_dirty import *

# Example data LINUX:
# Received: Time_Now:00~39:0:0:0|Date_Now:25/05/2026:0:0:0|Cpu_Utility:Total:2.08:0:100|Cpu_Utility:0:7.0:0:100|Cpu_Utility:1:0.07:0:100|Cpu_Utility:2:1.14:0:100|Cpu_Utility:3:1.23:0:100|Cpu_Utility:4:0.85:0:100|Cpu_Utility:5:0.06:0:100|Cpu_Utility:6:0.05:0:100|Cpu_Utility:7:2.2:0:100|Cpu_Utility:8:0.03:0:100|Cpu_Utility:9:5.07:0:100|Cpu_Utility:10:1.69:0:100|Cpu_Utility:11:5.52:0:100|Cpu_Utility:12:0.01:0:100|Cpu_Utility:13:0.67:0:100|Cpu_Utility:14:0.18:0:100|Cpu_Utility:15:0.01:0:100|Cpu_Utility:16:2.04:0:100|Cpu_Utility:17:0.01:0:100|Cpu_Utility:18:16.93:0:100|Cpu_Utility:19:0.49:0:100|Cpu_Utility:20:1.64:0:100|Cpu_Utility:21:0.12:0:100|Cpu_Utility:22:1.1:0:100|Cpu_Utility:23:1.72:0:100|Cpu_Utility:24:1.62:0:100|Cpu_Utility:25:5.99:0:100|Cpu_Utility:26:0.5:0:100|Cpu_Utility:27:5.24:0:100|Cpu_Utility:28:0.01:0:100|Cpu_Utility:29:1.65:0:100|Cpu_Utility:30:0.16:0:100|Cpu_Utility:31:1.61:0:100|Cpu_Clock:Total:4670.8603370361325:0:100|Cpu_Clock:0:5168.848:0:100|Cpu_Clock:1:5676.124:0:100|Cpu_Clock:2:5666.39:0:100|Cpu_Clock:3:5686.512:0:100|Cpu_Clock:4:5681.359:0:100|Cpu_Clock:5:624.194:0:100|Cpu_Clock:6:4047.763:0:100|Cpu_Clock:7:624.194:0:100|Cpu_Clock:8:4045.435:0:100|Cpu_Clock:9:5476.618:0:100|Cpu_Clock:10:5458.642:0:100|Cpu_Clock:11:624.194:0:100|Cpu_Clock:12:5475.87:0:100|Cpu_Clock:13:624.194:0:100|Cpu_Clock:14:5464.798:0:100|Cpu_Clock:15:624.194:0:100|Cpu_Clock:16:5458.664:0:100|Cpu_Clock:17:5477.297:0:100|Cpu_Clock:18:None:0:100|Cpu_Clock:19:None:0:100|Cpu_Clock:20:None:0:100|Cpu_Clock:21:None:0:100|Cpu_Clock:22:None:0:100|Cpu_Clock:23:None:0:100|Cpu_Clock:24:None:0:100|Cpu_Clock:25:None:0:100|Cpu_Clock:26:None:0:100|Cpu_Clock:27:None:0:100|Cpu_Clock:28:None:0:100|Cpu_Clock:29:None:0:100|Cpu_Clock:30:None:0:100|Cpu_Clock:31:None:0:100|Wattage:Compute Unit:55.55:0:100|Temperature:Compute Unit:50.9:0:100|Cpu_Memory:Used:5.204:0:100|Cpu_Memory:Available:88.98200000000001:0:100|Storage_Load:sdb:0.0:0:100|Storage_Load:sda:0.0:0:100|Storage_Load:nvme1n1:0.3:0:100|Storage_Load:nvme0n1:0.0:0:100|Storage_Load:loop9:0.0:0:100|Storage_Load:loop8:0.0:0:100|Storage_Load:loop7:0.0:0:100|Storage_Load:loop6:0.0:0:100|Storage_Load:loop5:0.0:0:100|Storage_Load:loop4:0.0:0:100|Storage_Load:loop3:0.0:0:100|Storage_Load:loop2:0.0:0:100|Storage_Load:loop16:0.0:0:100|Storage_Load:loop15:0.0:0:100|Storage_Load:loop14:0.0:0:100|Storage_Load:loop13:0.0:0:100|Storage_Load:loop12:0.0:0:100|Storage_Load:loop11:0.0:0:100|Storage_Load:loop10:0.0:0:100|Storage_Load:loop1:0.0:0:100|Storage_Load:loop0:0.0:0:100|Storage_Load:dm-2:0.0:0:100|Storage_Load:dm-1:0.3:0:100|Storage_Load:dm-0:0.3:0:100|Upload_Speed:Total:15831.04:15831.04:0|Download_Speed:Total:2263.04:2263.04:0|Gpu_Utility:Clock:72.0:0:100|Gpu_Clock:Clock:315.0:0:100|Gpu_Memory:Available:23.716:0:100|Gpu_Memory:Used:0.346:0:100|Wattage:Graphics:20.84:0:100|Temperature:Graphics:47.0:0:100|

# Example data WIN:
# WIN DATA: WIN DATA: Cpu_Utility:0:18.853533:0:99.397385|Gpu_Utility:Clock:18.853533:0:99.397385|Cpu_Utility:1:4.195106:0:99.9864|Gpu_Utility:Clock:4.195106:0:99.9864|Cpu_Utility:2:32.363247:0:99.99473|Gpu_Utility:Clock:32.363247:0:99.99473|Cpu_Utility:3:10.543042:0:100|Gpu_Utility:Clock:10.543042:0:100|Cpu_Utility:4:7.470995:0:94.03468|Gpu_Utility:Clock:7.470995:0:94.03468|Cpu_Utility:5:3.0554533:0:94.01741|Gpu_Utility:Clock:3.0554533:0:94.01741|Cpu_Utility:6:10.958719:0:97.67065|Gpu_Utility:Clock:10.958719:0:97.67065|Cpu_Utility:7:7.599682:0:99.988976|Gpu_Utility:Clock:7.599682:0:99.988976|Cpu_Utility:8:3.4331858:0:93.80159|Gpu_Utility:Clock:3.4331858:0:93.80159|Cpu_Utility:9:2.5790155:0:96.95276|Gpu_Utility:Clock:2.5790155:0:96.95276|Cpu_Utility:10:9.6030655:0:99.97913|Gpu_Utility:Clock:9.6030655:0:99.97913|Cpu_Utility:11:49.551224:0:100|Gpu_Utility:Clock:49.551224:0:100|Cpu_Utility:12:1.3555646:0:94.30297|Gpu_Utility:Clock:1.3555646:0:94.30297|Cpu_Utility:13:1.4119744:0:93.02029|Gpu_Utility:Clock:1.4119744:0:93.02029|Cpu_Utility:14:4.0292144:0:93.471756|Gpu_Utility:Clock:4.0292144:0:93.471756|Cpu_Utility:15:1.689738:0:94.39784|Gpu_Utility:Clock:1.689738:0:94.39784|Cpu_Utility:16:1.6731441:0:93.17457|Gpu_Utility:Clock:1.6731441:0:93.17457|Cpu_Utility:17:7.944578:0:93.2498|Gpu_Utility:Clock:7.944578:0:93.2498|Cpu_Utility:18:1.5661716:0:93.178474|Gpu_Utility:Clock:1.5661716:0:93.178474|Cpu_Utility:19:1.2624443:0:94.07797|Gpu_Utility:Clock:1.2624443:0:94.07797|Cpu_Utility:20:2.399224:0:92.15433|Gpu_Utility:Clock:2.399224:0:92.15433|Cpu_Utility:21:0:0:93.25683|Gpu_Utility:Clock:0:0:93.25683|Cpu_Utility:22:7.8578353:0:93.003586|Gpu_Utility:Clock:7.8578353:0:93.003586|Cpu_Utility:23:1.1851907:0:93.544685|Gpu_Utility:Clock:1.1851907:0:93.544685|Cpu_Utility:24:1.76512:0:94.004974|Gpu_Utility:Clock:1.76512:0:94.004974|Cpu_Utility:25:1.2918413:0:95.830986|Gpu_Utility:Clock:1.2918413:0:95.830986|Cpu_Utility:26:1.3716102:0:92.35369|Gpu_Utility:Clock:1.3716102:0:92.35369|Cpu_Utility:27:1.1729836:0:93.20761|Gpu_Utility:Clock:1.1729836:0:93.20761|Cpu_Utility:28:1.1315227:0:93.182655|Gpu_Utility:Clock:1.1315227:0:93.182655|Cpu_Utility:29:0:0:91.890656|Gpu_Utility:Clock:0:0:91.890656|Cpu_Utility:30:3.8383543:0:99.82572|Gpu_Utility:Clock:3.8383543:0:99.82572|Cpu_Utility:31:1.3999999:0:100|Gpu_Utility:Clock:1.3999999:0:100|Cpu_Utility:Total:6.1444163:0:93.85702|Cpu_Utility:32:49.551224:11.890531:100|Gpu_Utility:Clock:49.551224:11.890531:100|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:4066.2056:70.10698:14582.255|Gpu_Clock:Clock:4066.2056:70.10698:14582.255|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:4066.2056:0:14582.255|Gpu_Clock:Clock:4066.2056:0:14582.255|Cpu_Clock:0:2313.5308:0:14583.542|Gpu_Clock:Clock:2313.5308:0:14583.542|Cpu_Clock:0:2313.5308:0:14583.542|Gpu_Clock:Clock:2313.5308:0:14583.542|Cpu_Clock:0:2313.5308:0:14583.542|Gpu_Clock:Clock:2313.5308:0:14583.542|Cpu_Clock:0:2313.5308:35.053482:14583.542|Gpu_Clock:Clock:2313.5308:35.053482:14583.542|Cpu_Clock:0:2313.5308:35.053482:14583.542|Gpu_Clock:Clock:2313.5308:35.053482:14583.542|Cpu_Clock:0:2313.5308:35.053493:14583.542|Gpu_Clock:Clock:2313.5308:35.053493:14583.542|Cpu_Clock:0:2313.5308:35.053493:14583.542|Gpu_Clock:Clock:2313.5308:35.053493:14583.542|Cpu_Clock:0:2313.5308:0:14583.542|Gpu_Clock:Clock:2313.5308:0:14583.542|Cpu_Memory:Used:41.361664:10.850719:41.94874|Gpu_Memory:Used:41.361664:10.850719:41.94874|Cpu_Memory:Available:52.2974:51.710327:82.80835|Gpu_Memory:Available:52.2974:51.710327:82.80835|Gpu_Memory:Used:64.79904:11.72942:122.21582|Gpu_Memory:Available:34.86002:0.21653748:87.92964|Gpu_Memory:Available:2.0135233:2.0118906:2.0199804|Gpu_Memory:Used:0.008242187:0.0017851562:0.009875|Gpu_Memory:Used:0.017316407:0.0005:0.019519532|Gpu_Memory:Available:47.936127:47.93392:47.95294|Gpu_Memory:Used:0.008:0.001:0.009|Gpu_Memory:Available:2.04:2.039:2.047|Gpu_Clock:Clock:600:600:600|Gpu_Utility:Clock:0:0:0|Gpu_Clock:Clock:210:210:2565|Gpu_Utility:Clock:19:0:81|Gpu_Memory:Used:1.9888047:0.6646094:2.1145117|Gpu_Memory:Used:0.065695316:0.059191406:0.24322656|Gpu_Memory:Available:22.157:22.032:23.478|Gpu_Memory:Used:2.406:1.085:2.531|Storage_Load:Total Activity:0.004528962:0:100|Storage_Load:Total Activity:0.006024374:0:100|Storage_Load:Total Activity:0.006579813:0:100|Cpu_Clock:Total:5289:-1:5461|Wattage:AMD Ryzen 9 9950X:49.307743:0.026933402:165.94771|Wattage:AMD Radeon(TM) Graphics:21:9:65|Wattage:NVIDIA GeForce RTX 4090:16.29:9.854:68.957|Temperature:AMD Ryzen 9 9950X:60.625008:39.5:90.25001|Temperature:AMD Radeon(TM) Graphics:50:50:57|Temperature:NVIDIA GeForce RTX 4090:51:42:54|Time_Now:20~34:0:0:0|Date_Now:5/30/2026:0:0:0|Download_Speed:Bluetooth Network Connection:0:0:0|Download_Speed:Local Area Connection* 9:0:0:0|Download_Speed:OpenVPN Data Channel Offload for Surfshark:0:0:0|Download_Speed:Wi-Fi 3:3049.6687:1699.1289:18797516|Upload_Speed:Bluetooth Network Connection:0:0:0|Upload_Speed:Local Area Connection* 9:0:0:0|Upload_Speed:OpenVPN Data Channel Offload for Surfshark:0:0:0|Upload_Speed:Wi-Fi 3:198249.81:3263.019:1360948.6|Dark_Mode:0:0:0:0|!


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
