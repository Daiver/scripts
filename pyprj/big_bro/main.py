import subprocess

if __name__ == '__main__':
    def test_num(num):
        try:
            return int(num)
        except:
            return False
    
    p = subprocess.Popen(['ps', '-e'], stdout=subprocess.PIPE)
    raw_string, e = p.communicate()
    strings_arr = raw_string.split('\n')
    process_dict = {}
    for string in strings_arr:
        splted = string.split()
        key, value = None, None
        if len(splted) == 0: continue
        for item in splted:
            if test_num(item):
                key = int(item)
                break
        value = splted[-1]
        process_dict[key] = value

    print process_dict

