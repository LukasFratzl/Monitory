# Example data:
# Received: Time_Now:00~39:0:0:0|Date_Now:25/05/2026:0:0:0|Cpu_Utility:Total:2.08:0:100|Cpu_Utility:0:7.0:0:100|Cpu_Utility:1:0.07:0:100|Cpu_Utility:2:1.14:0:100|Cpu_Utility:3:1.23:0:100|Cpu_Utility:4:0.85:0:100|Cpu_Utility:5:0.06:0:100|Cpu_Utility:6:0.05:0:100|Cpu_Utility:7:2.2:0:100|Cpu_Utility:8:0.03:0:100|Cpu_Utility:9:5.07:0:100|Cpu_Utility:10:1.69:0:100|Cpu_Utility:11:5.52:0:100|Cpu_Utility:12:0.01:0:100|Cpu_Utility:13:0.67:0:100|Cpu_Utility:14:0.18:0:100|Cpu_Utility:15:0.01:0:100|Cpu_Utility:16:2.04:0:100|Cpu_Utility:17:0.01:0:100|Cpu_Utility:18:16.93:0:100|Cpu_Utility:19:0.49:0:100|Cpu_Utility:20:1.64:0:100|Cpu_Utility:21:0.12:0:100|Cpu_Utility:22:1.1:0:100|Cpu_Utility:23:1.72:0:100|Cpu_Utility:24:1.62:0:100|Cpu_Utility:25:5.99:0:100|Cpu_Utility:26:0.5:0:100|Cpu_Utility:27:5.24:0:100|Cpu_Utility:28:0.01:0:100|Cpu_Utility:29:1.65:0:100|Cpu_Utility:30:0.16:0:100|Cpu_Utility:31:1.61:0:100|Cpu_Clock:Total:4670.8603370361325:0:100|Cpu_Clock:0:5168.848:0:100|Cpu_Clock:1:5676.124:0:100|Cpu_Clock:2:5666.39:0:100|Cpu_Clock:3:5686.512:0:100|Cpu_Clock:4:5681.359:0:100|Cpu_Clock:5:624.194:0:100|Cpu_Clock:6:4047.763:0:100|Cpu_Clock:7:624.194:0:100|Cpu_Clock:8:4045.435:0:100|Cpu_Clock:9:5476.618:0:100|Cpu_Clock:10:5458.642:0:100|Cpu_Clock:11:624.194:0:100|Cpu_Clock:12:5475.87:0:100|Cpu_Clock:13:624.194:0:100|Cpu_Clock:14:5464.798:0:100|Cpu_Clock:15:624.194:0:100|Cpu_Clock:16:5458.664:0:100|Cpu_Clock:17:5477.297:0:100|Cpu_Clock:18:None:0:100|Cpu_Clock:19:None:0:100|Cpu_Clock:20:None:0:100|Cpu_Clock:21:None:0:100|Cpu_Clock:22:None:0:100|Cpu_Clock:23:None:0:100|Cpu_Clock:24:None:0:100|Cpu_Clock:25:None:0:100|Cpu_Clock:26:None:0:100|Cpu_Clock:27:None:0:100|Cpu_Clock:28:None:0:100|Cpu_Clock:29:None:0:100|Cpu_Clock:30:None:0:100|Cpu_Clock:31:None:0:100|Wattage:Compute Unit:55.55:0:100|Temperature:Compute Unit:50.9:0:100|Cpu_Memory:Used:5.204:0:100|Cpu_Memory:Available:88.98200000000001:0:100|Storage_Load:sdb:0.0:0:100|Storage_Load:sda:0.0:0:100|Storage_Load:nvme1n1:0.3:0:100|Storage_Load:nvme0n1:0.0:0:100|Storage_Load:loop9:0.0:0:100|Storage_Load:loop8:0.0:0:100|Storage_Load:loop7:0.0:0:100|Storage_Load:loop6:0.0:0:100|Storage_Load:loop5:0.0:0:100|Storage_Load:loop4:0.0:0:100|Storage_Load:loop3:0.0:0:100|Storage_Load:loop2:0.0:0:100|Storage_Load:loop16:0.0:0:100|Storage_Load:loop15:0.0:0:100|Storage_Load:loop14:0.0:0:100|Storage_Load:loop13:0.0:0:100|Storage_Load:loop12:0.0:0:100|Storage_Load:loop11:0.0:0:100|Storage_Load:loop10:0.0:0:100|Storage_Load:loop1:0.0:0:100|Storage_Load:loop0:0.0:0:100|Storage_Load:dm-2:0.0:0:100|Storage_Load:dm-1:0.3:0:100|Storage_Load:dm-0:0.3:0:100|Upload_Speed:Total:15831.04:15831.04:0|Download_Speed:Total:2263.04:2263.04:0|Gpu_Utility:Clock:72.0:0:100|Gpu_Clock:Clock:315.0:0:100|Gpu_Memory:Available:23.716:0:100|Gpu_Memory:Used:0.346:0:100|Wattage:Graphics:20.84:0:100|Temperature:Graphics:47.0:0:100|


export_stats_json =	{"Time_Now": "",
			"Date_Now": "",
			"Cpu_Utility_Total": 0,
			"Cpu_Utility_Thread": [],
			"Cpu_Clock_Average": 0,
			"Cpu_Clock_Thread": [],
			"Cpu_Wattage": 0,
			"Cpu_Temperature": 0,
			"Cpu_Memory_Available": 0,
			"Cpu_Memory_Used": 0,
			"Storage_Load": {},
			"Net_Upload_Speed": 0,
			"Net_Download_Speed": 0,
			"Gpu_Utility": 0,
			"Gpu_Clock": 0,
			"Gpu_Memory_Available": 0,
			"Gpu_Memory_Used": 0,
			"Gpu_Wattage": 0,
			"Gpu_Temperature": 0}
			
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
        
    export_stats_json["Cpu_Utility_Thread"] = []
    export_stats_json["Cpu_Clock_Thread"] = []
    export_stats_json["Storage_Load"] = dict()
    
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
            if "Compute Unit" in sub_label:
                export_stats_json["Cpu_Wattage"] = current_val
            if "Graphics" in sub_label:
                export_stats_json["Gpu_Wattage"] = current_val
                
        if "Temperature" in label:
            if "Compute Unit" in sub_label:
                export_stats_json["Cpu_Temperature"] = current_val
            if "Graphics" in sub_label:
                export_stats_json["Gpu_Temperature"] = current_val
                
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
            
            
