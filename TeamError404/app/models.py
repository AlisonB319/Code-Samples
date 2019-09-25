from app import db, login
from werkzeug.security import generate_password_hash, check_password_hash
from flask_login import UserMixin
    
class Student(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    student_id = db.Column(db.String(10), nullable=False)
    fname = db.Column(db.String(128), nullable=False)
    lname = db.Column(db.String(128), nullable=False)
    email = db.Column(db.String(128), nullable=False, unique=True)
    major = db.Column(db.String(64), nullable=False)
    gpa = db.Column(db.String(5), nullable=False)
    grad_date = db.Column(db.String(10), nullable=False)
    password_hash = db.Column(db.String(128))
    
    def __repr__(self):
        return '<Student {} {}>'.format(self.fname, self.lname)

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)



class Instructor(UserMixin, db.Model): 
    id = db.Column(db.Integer, primary_key=True, default=1000)
    faculty_id = db.Column(db.String(9), nullable=False)
    fname= db.Column(db.String(128), nullable=False)
    lname= db.Column(db.String(128), nullable=False)
    email = db.Column(db.String(120), nullable=False, unique=True)
    phone = db.Column(db.String(10), nullable=False)
    office = db.Column(db.String(28), nullable=False)
    password_hash = db.Column(db.String(128))

    def __repr__(self):
        return '<Instructor {} {}>'.format(self.fname, self.lname)

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)



class Courses(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    course_name = db.Column(db.String(10), nullable=False)
    title = db.Column(db.String(64), nullable=False)
    description = db.Column(db.String(1028), nullable=False)

    def __repr__(self):
        return '<Course {}>'.format(self.course_name)

class InstructorCourse(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    faculty_id = db.Column(db.String(10), nullable=False)
    course_name = db.Column(db.String(10), nullable=False)

    def __repr__(self):
        return '<Instructor Course {} {}'.format(self.faculty_id, self.course_name)

class CourseTA(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    student_id = db.Column(db.String(10), nullable=False)
    faculty_id = db.Column(db.String(10), nullable=False)
    course_name = db.Column(db.String(10), nullable=False)
    grade = db.Column(db.String(5), nullable=False)
    semester_taken_course = db.Column(db.String(10), nullable=False)
    application_date = db.Column(db.String(16), nullable=False)
    prior_ta = db.Column(db.String(1), nullable=False)
    application_status = db.Column(db.String(16), nullable=False)

    def __repr__(self):
        return '<Course TA {} {}>'.format(self.student_id, self.course_name)


@login.user_loader
def load_user(id):
    print("getting user")
    check=int(id)
    if check >= 1000:
        return Instructor.query.get(int(id))

    return Student.query.get(int(id))
