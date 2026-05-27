import json

save_data_archtyoe = {
    "dark_mode": True,
    "font_size": 45,
    "IPs": []
}

save_data_file = "assets/saved/app_data.json"

def read_data():
    found_data = False
    data = save_data_archtyoe
    try:
        with open(save_data_file, "r") as f:
            data = json.load(f)
        found_data = True
    except:
        if not found_data:
            try:
                with open(save_data_file, "w") as f:
                    json.dump(data, f)
            except:
                pass
    return data
    
def write_data(data):
    try:
        with open(save_data_file, "w") as f:
            json.dump(data, f)
        return True
    except:
        return False
            
    
