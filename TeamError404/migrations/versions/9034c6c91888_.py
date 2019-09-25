"""empty message

Revision ID: 9034c6c91888
Revises: 
Create Date: 2018-11-06 22:23:16.988398

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = '9034c6c91888'
down_revision = None
branch_labels = None
depends_on = None


def upgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.create_table('courseTA',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('student_id', sa.String(length=10), nullable=False),
    sa.Column('faculty_id', sa.String(length=10), nullable=False),
    sa.Column('course_name', sa.String(length=10), nullable=False),
    sa.Column('grade', sa.String(length=5), nullable=False),
    sa.Column('semester_taken_course', sa.String(length=10), nullable=False),
    sa.Column('application_date', sa.String(length=16), nullable=False),
    sa.Column('prior_ta', sa.String(length=1), nullable=False),
    sa.Column('application_status', sa.String(length=16), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )
    op.create_table('courses',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('course_name', sa.String(length=10), nullable=False),
    sa.Column('title', sa.String(length=64), nullable=False),
    sa.Column('description', sa.String(length=1028), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )
    op.create_table('instructor',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('faculty_id', sa.String(length=9), nullable=False),
    sa.Column('fname', sa.String(length=128), nullable=False),
    sa.Column('lname', sa.String(length=128), nullable=False),
    sa.Column('email', sa.String(length=120), nullable=False),
    sa.Column('phone', sa.String(length=10), nullable=False),
    sa.Column('office', sa.String(length=28), nullable=False),
    sa.Column('password_hash', sa.String(length=128), nullable=True),
    sa.PrimaryKeyConstraint('id'),
    sa.UniqueConstraint('email')
    )
    op.create_table('instructor_course',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('faculty_id', sa.String(length=10), nullable=False),
    sa.Column('course_name', sa.String(length=10), nullable=False),
    sa.PrimaryKeyConstraint('id')
    )
    op.create_table('student',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('student_id', sa.String(length=10), nullable=False),
    sa.Column('fname', sa.String(length=128), nullable=False),
    sa.Column('lname', sa.String(length=128), nullable=False),
    sa.Column('email', sa.String(length=128), nullable=False),
    sa.Column('major', sa.String(length=64), nullable=False),
    sa.Column('gpa', sa.String(length=5), nullable=False),
    sa.Column('grad_date', sa.String(length=10), nullable=False),
    sa.Column('password_hash', sa.String(length=128), nullable=True),
    sa.PrimaryKeyConstraint('id'),
    sa.UniqueConstraint('email')
    )
    # ### end Alembic commands ###


def downgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_table('student')
    op.drop_table('instructor_course')
    op.drop_table('instructor')
    op.drop_table('courses')
    op.drop_table('courseTA')
    # ### end Alembic commands ###
