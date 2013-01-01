
class Component:

    def __init__(self):
        self.sub_components = []
        self.name = ''
        
        self.requires_dependences = []
        self.provides_rules = []

        self.settings = {}
