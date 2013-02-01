from direct.showbase.ShowBase import ShowBase
from direct.actor.Actor import Actor
from math import pi

import sho

def cooTransform(cp):
    #cp.y, cp.z = cp.z, cp.y
    #cp.ty, cp.tz = cp.tz, cp.ty
    return cp

class MyApp(ShowBase):
 
    def __init__(self):
        ShowBase.__init__(self)
        # self.cube = Actor("models/panda-model", {"walk": "models/panda-walk4"})
        # self.cube.reparentTo(self.render)
        # self.cube.setScale(0.005, 0.005, 0.005)
        # self.cube.setPos(-3, 10, 0)
        # self.cube.loop("walk")

	self.cube = self.loader.loadModel("box")
        self.cube.reparentTo(self.render)
        self.cube.setScale(1, 1, 1)
        self.cube.setPos(-3, 10, 0)

        self.environ = self.loader.loadModel("models/environment")
        self.environ.reparentTo(self.render)
        self.environ.setScale(0.25, 0.25, 0.25)
        self.environ.setPos(-8, 42, -10)

        self.taskMgr.add(self.taskFunction, "test")

    def taskFunction(self, task):
        camPos = cooTransform(sho.getCamPos())
        self.cube.setX(camPos.x)
        self.cube.setY(camPos.z)
        #self.cube.setZ(camPos.y)

        #self.camera.setX(camPos.x)
        # self.camera.setY(self.camera.getY() + 5)
        #self.camera.setZ(camPos.y)
        angDegX = (camPos.tx / pi) * 180.0
        angDegY = (camPos.ty / pi) * 180.0
        angDegZ = (camPos.tz / pi) * 180.0
        #print(camPos.x, camPos.y, camPos.z)
        print angDegY
        #self.cube.setColor(240, 90, 8, 240)
        #self.camera.setHpr(-angDegY, 0, 0)
        self.cube.setHpr(-angDegY, 0, 0)
        #self.cameraPositionNode.setHpr(angGe
        # self.cube.setHpr(angDegX, angDegY, angDegZ)
        return task.cont

app = MyApp()
app.run()

