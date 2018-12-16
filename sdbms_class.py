from sdbms_base_class import SdbmsBaseClass
from student import Student


class SdbmsClass(SdbmsBaseClass):
    """ This class will hold data for a SDBMS class """

    def __init__(self):
        super().__init__()
        self.__class_room_number = 0
        self.__number_of_students = 0
        self.__students = Student()

    @property
    def class_room_number(self):
        return self.__class_room_number

    @class_room_number.setter
    def class_room_number(self, value):
        self.__class_room_number = value

    @property
    def number_of_students(self):
        return self.__number_of_students

    @number_of_students.setter
    def number_of_students(self, value):
        self.__number_of_students = value

    @property
    def students(self):
        return self.__students

    @students.setter
    def students(self, value):
        self.__students = value
