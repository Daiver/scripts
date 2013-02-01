from direct.showbase.ShowBase import ShowBase
 
import sho

class MyApp(ShowBase):
 
    def __init__(self):
        ShowBase.__init__(self)
        self.cube = self.loader.loadModel("panda-model")
        self.cube.reparentTo(self.render)
        self.cube.setScale(1)
        self.cube.setPos(-3, 10, 0)

        self.environ = self.loader.loadModel("models/environment")
        self.environ.reparentTo(self.render)
        self.environ.setScale(0.25, 0.25, 0.25)
        self.environ.setPos(-8, 42, -10)

        self.taskMgr.add(self.taskFunction, "test")
    
    def taskFunction(self, task):
        camPos = sho.getCamPos()
        self.cube.setX(camPos.x)
        self.cube.setY(camPos.y)
        self.cube.setZ(camPos.z)
        return task.cont

app = MyApp()
app.run()

