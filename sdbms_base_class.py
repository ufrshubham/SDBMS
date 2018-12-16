
class SdbmsBaseClass(object):
    """ Base class for all sdbms classes """

    # class wide counter
    __object_id = 0

    def __init__(self):
        SdbmsBaseClass.__object_id += 1
        self.__id = SdbmsBaseClass.__object_id

    @property
    def obj_id(self):
        return self.__id
