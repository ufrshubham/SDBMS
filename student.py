from sdbms_base_class import SdbmsBaseClass
from subject_marks import SubjectMarks


class Student(SdbmsBaseClass):
    """ This class hold data of a SDBMS student """

    def __init__(self):
        super().__init__()

        self.__name = ""
        self.__class_room_number = 0
        self.__roll_number = 0
        self.__subject_marks = SubjectMarks()

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    @property
    def class_room_number(self):
        return self.__class_room_number

    @class_room_number.setter
    def class_room_number(self, value):
        self.__class_room_number = value

    @property
    def roll_number(self):
        return self.__roll_number

    @roll_number.setter
    def roll_number(self, value):
        self.__roll_number = value

    @property
    def marks(self):
        return self.__subject_marks.marks

    @marks.setter
    def marks(self, value):
        self.__subject_marks.marks = value
