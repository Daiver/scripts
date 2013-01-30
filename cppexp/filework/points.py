try:
    import bpy
except:
    print('Work not from blender!')

dir_path = '/home/kirill/ScaViSLAM/svs_build/dumps/'
file_path = dir_path + '187'

'''
def addpoints(f):
    for i in range(10):
        f(location=(-1, -i, i), size=0.01)

def addpointsshort():
    addpoints(bpy.ops.mesh.primitive_ico_sphere_add)
'''

def lps(fnumber):
    file_path = dir_path + str(fnumber)
    with open(file_path) as f:
        s = f.readline()
        loc = [float(x) for x in s.split(' ')]
        #loc[1], loc[2] = -loc[2], loc[1]
        loc[1], loc[2] = loc[2], -loc[1]
        #s = f.readline()
        #rot = [float(x) for x in s.split(' ')]
        #rot[1], rot[2] = rot[2], -rot[1]
        #bpy.ops.mesh.primitive_cone_add(location=loc, rotation=rot)
        bpy.ops.mesh.primitive_ico_sphere_add(location=loc, size=1.0)
        for s in f:
            loc = [float(x) for x in s.split(' ')]
            loc[1], loc[2] = loc[2], -loc[1]
            bpy.ops.mesh.primitive_ico_sphere_add(location=loc, size=0.2)
    
if __name__ == "__main__":
    with open(file_path) as f:
        for s in f:
            print(s)

#import imp
#foo = imp.load_source('points', '/home/kirill/points.py')
#
#
