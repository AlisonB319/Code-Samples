from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, BooleanField, SubmitField
from wtforms.validators import DataRequired, ValidationError, Email, EqualTo
from app.models import Instructor, Student


class LoginForm(FlaskForm):
    email = StringField('Email', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Log In')

class RegisterInstructorForm(FlaskForm):
    faculty_id = StringField('Faculty ID', validators=[DataRequired()])
    fname = StringField('First Name', validators=[DataRequired()])
    lname = StringField('Last Name', validators=[DataRequired()])
    email = StringField('Email', validators=[DataRequired()])
    phone = StringField('Phone Number', validators=[DataRequired()])
    office = StringField('Office', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Create Account')

    def validate_email(self, email):
        user = Instructor.query.filter_by(email=email.data).first()
        if user is not None:
            raise ValidationError('Please use a different email address')


class RegisterStudentForm(FlaskForm):
    student_id= StringField('Student ID', validators=[DataRequired()])
    fname = StringField('First Name', validators=[DataRequired()])
    lname = StringField('Last Name', validators=[DataRequired()])
    major = StringField('major', validators=[DataRequired()])
    gpa = StringField('GPA', validators=[DataRequired()])
    grad_date = StringField('Grad Date', validators=[DataRequired()])    
    email = StringField('Email', validators=[DataRequired()])
    password = PasswordField('Password', validators=[DataRequired()])
    submit = SubmitField('Create Account')

    def validate_email(self, email):   
        user = Student.query.filter_by(email=email.data).first()
        if user is not None:
            raise ValidationError('Please use a different email address')
            print('please use a different email address')

class CourseForm(FlaskForm):
    course_name = StringField('Course Name', validators=[DataRequired()])
    title = StringField('Title', validators=[DataRequired()])
    description = StringField('Description', validators=[DataRequired()])
    submit = SubmitField('Add a Course')

class EditInstructorForm(FlaskForm):
    fname = StringField('First Name')
    lname = StringField('Last Name')
    phone = StringField('Phone Number')
    office = StringField('Office')
    password = PasswordField('Password')
    submit = SubmitField('Edit Account')

class EditStudentForm(FlaskForm):
    fname = StringField('First Name')
    lname = StringField('Last Name')
    major = StringField('major')
    gpa = StringField('GPA')
    grad_date = StringField('Grad Date')    
    password = PasswordField('Password')
    submit = SubmitField('Edit Account')