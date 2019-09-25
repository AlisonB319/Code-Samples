import os
import sys
from app import app, db
from sqlite3 import dbapi2 as sqlite3
from flask import Flask, request, session, g, redirect, url_for, abort, \
    render_template, flash
from flask_login import current_user, login_user, logout_user, login_required
from app.models import Student, Instructor, Courses
from app.form import LoginForm, RegisterInstructorForm, RegisterStudentForm, CourseForm, EditInstructorForm, EditStudentForm

@app.context_processor
def override_url_for():
    return dict(url_for=dated_url_for)

def dated_url_for(endpoint, **values):
    if endpoint == 'static':
        filename = values.get('filename', None)
        if filename:
            file_path = os.path.join(app.root_path,
                                endpoint, filename)
            values['q'] = int(os.stat(file_path).st_mtime)
    return url_for(endpoint, **values)
    

@app.route('/login', methods=['GET', 'POST'])
def login():
    print("In route login. ")
    print("current user: ", current_user)
    if current_user.is_authenticated:
        print("user {} is authenticated".format(current_user))
        return redirect(url_for('user'))

    print('form:')
    form = LoginForm()
    print('form.email = ', request.form.get('email'))
    print('form.password = ', request.form.get('password'))

    instructors = Instructor.query.filter_by(email=request.form.get('email'))
    for i in instructors:
        if request.form.get('email') == i.email:
            if i.check_password(request.form.get('password')) == True:
                login_user(i)
                print("Instructor successful")
                return redirect(url_for('user'))

    students = Student.query.filter_by(email=request.form.get('email'))
    for i in students:
        print(i)
        if request.form.get('email') == i.email:
            if i.check_password(request.form.get('password')) == True:
                login_user(i)
                print("Student successful")
                return redirect(url_for('user'))
                
    print('at end of login')
    return render_template('login.html', form=form)

@app.route('/logout')
def logout():
    logout_user()
    print("user logging out")
    return redirect(url_for('login'))

@app.route('/')
@app.route('/index')
@login_required
def user():
    print("in user")
    if current_user.id >= 1000:
        print("is instructor")
        return render_template('instructor_homepage.html', user=current_user)
    else:
        print("is student")
        return render_template("student_homepage.html", user=current_user)

@app.route('/create_faculty', methods=['GET', 'POST'])
def create_faculty():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = RegisterInstructorForm()
    print("form = ", form)
    print("validation:\t", form.validate_on_submit())
    if form.validate_on_submit():
        print("in form validate on submit")
        user = Instructor(faculty_id=form.faculty_id.data, fname=form.fname.data,
        lname=form.lname.data, email=form.email.data, phone=form.phone.data, office=form.office.data)
        user.set_password(form.password.data)
        db.session.add(user)
        db.session.commit()
        flash("Congrats! You're now a registered user")
        return redirect(url_for('login'))
    return render_template('create_faculty_account.html', form=form)

@app.route('/create_student', methods=['GET', 'POST'])
def create_student():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = RegisterStudentForm()
    print("form = ", form)
    print("validation", form.validate_on_submit())
    if form.validate_on_submit():
        print("in form validate on submit")
        user = Student(student_id=form.student_id.data, fname=form.fname.data,
        lname=form.lname.data, email=form.email.data, major=form.major.data,
        gpa=form.gpa.data, grad_date=form.grad_date.data)
        print(form.password.data)
        user.set_password(form.password.data)
        db.session.add(user)
        db.session.commit()
        flash("Congrats! You're now a registered user")
        return redirect(url_for('login'))
    return render_template('create_student_account.html', form=form)

@login_required
@app.route('/create_course', methods=['GET', 'POST'])
def create_course():
    form = CourseForm()
    print("form = ", form)
    print("validation:\t", form.validate_on_submit())
    if form.validate_on_submit():
        print("in form validate on submit")
        course = Courses(course_name=form.course_name.data, title=form.title.data, description=form.description.data)
        db.session.add(course)
        db.session.commit()
        flash("Congrats! You've added a course")
        return redirect(url_for('user'))
    return render_template('instructor_add_course.html', form=form)

@login_required
@app.route('/edit_student', methods=['GET', 'POST'])
def edit_student():
    form = EditStudentForm()
    print("form_edit = ", form)
    print("validation", form.validate_on_submit())
    if form.validate_on_submit():
        print("in form validate on submit")

        if request.form.get('fname') is not "":
            current_user.fname = request.form.get('fname')
        
        if request.form.get('lname') is not "":
            current_user.lname = request.form.get('lname')
        
        if request.form.get('major') is not "":
            current_user.major = request.form.get('major')

        if request.form.get('gpa') is not "":
            current_user.gpa = request.form.get('gpa')

        if request.form.get('grad_date') is not "":
            current_user.grad_date = request.form.get('grad_date')

        if request.form.get('password') is not "":
            current_user.set_password(request.form.get('password'))

        save_student_changes(Student.query.filter_by(id=current_user.id).first(), current_user)

        flash("Congrats! You have made an edit-- student")
        return redirect(url_for('user'))
    return render_template('edit_profile_student.html', form=form)


@login_required
@app.route('/edit_instructor', methods=['GET', 'POST'])
def edit_instructor():
    form = EditInstructorForm()
    print("EDITTING PROFILE:")
    print("validation:\t", form.validate_on_submit())
    if form.validate_on_submit():
        user = current_user
        print("in form validate on submit")
        print("fname: ", current_user.fname)
        if request.form.get('fname') is not "":
            print("user fname: ", user.fname)
            user.fname = request.form.get('fname')
            print("current_user fname: ", user.fname)
            
        if request.form.get('lname') is not "":
            user.lname = request.form.get('lname')             
       
        if request.form.get('phone') is not "":
            user.phone = request.form.get('phone')                           

        if request.form.get('office') is not "":          
            user.office = request.form.get('office')

        if request.form.get('password') is not "":
            user.set_password(request.form.get('password'))

        save_instructor_changes(Instructor.query.filter_by(id=current_user.id).first(), user)
        flash("Congrats! You have made an edit-- faculty")
        return redirect(url_for('user'))
    return render_template('edit_profile_faculty.html', form=form)

def save_student_changes(student, form):
    student.fname = form.fname
    student.lname = form.lname
    student.major = form.major
    student.gpa = form.gpa
    student.grad_date = form.grad_date
    student.password_hash = form.password_hash

    db.session.commit()

def save_instructor_changes(instructor, form):
    instructor = Instructor()
    instructor.fname = form.fname
    instructor.lname = form.lname
    instructor.phone = form.phone
    instructor.office = form.office
    instructor.password_hash = form.password_hash

    db.session.commit()                