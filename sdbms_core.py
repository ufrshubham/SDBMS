from sdbms_base_class import SdbmsBaseClass
from sdbms_class import SdbmsClass


class SdbmsCore(SdbmsBaseClass):
    """ This class will hold a list of all sdbms classes """

    def __init__(self):
        super().__init__()
        self.__sdbms_classes = []

    @property
    def classes(self):
        return self.__sdbms_classes

    def add_class(self, value):
        """ Will add given object to sdbms classes list. Raises value error if value is not a SdbmsClass object. """
        if isinstance(value, SdbmsClass):
            self.classes.append(value)
        else:
            raise ValueError
