#include <string.h>
#include <stdio.h>
#include <stdlib.h>		// For built-in malloc that returns void *

#include "Dictionary.h"
#include "Enrollment.h"
// create global dictionaries
dictionary CourseDict;
dictionary StudentDict;

void addCourse(course_element *e) {
  if(find(&CourseDict, e->key) != NULL) {
    printf("Course already exists.");
    return;
  }
  insert(&CourseDict, (element*) e);
}

void enroll(char *s_key, char *c_key) {
  node_t* student_node;
  node_t* course_node;
  
  //course_node->value;
  student_node->value = NULL;

  node_t* student_list;
  node_t* course_list;

  student_node = find(&StudentDict, s_key);
  course_node = find(&CourseDict, c_key);
  
  if (course_node == NULL) {
    printf("Course does not exist.");
    return;
  }
  
  if (student_node == NULL) {
    student_element* new_student = (student_element*) malloc(sizeof(student_element));
    memcpy(new_student->key, s_key, 5);
    new_student->value = (student_value*) newNode('s');

    new_student->value->num_courses = 0;
    new_student->value->list = NULL;
   
    insert(&StudentDict, (element*) new_student);
    student_node = find(&StudentDict, s_key);   
    student_node->value = new_student; 
  }

  node_t* course_list_head = student_node->value->list;           // get head of student's list of courses
  if (findList(course_list_head, c_key) != NULL) {
    printf("Student is already enrolled in this course.");
  }
  
  if (course_node->value->num_students < course_node->value->capacity) {
    node_t* new_student = student_node;
    memcpy(new_student->key, s_key, 5);
    new_student->value = student_node->value;
    new_student->next = NULL;
    new_student->prev = NULL;
    insertList(&course_node->value->list, new_student);
    course_node->value->num_students++;
  }

  if (student_node->value->num_courses == 2) {
    printf("Student is already enrolled in 2 courses");
    return;
  } else {
    node_t* new_course = course_node;
    memcpy(new_course->key, c_key, 5);
    new_course->value = course_node->value;
    new_course->next = NULL;
    new_course->prev = NULL;
    insertList(&student_node->value->list, new_course);
    student_node->value->num_courses++;
  }

}

int main() {
  char line[100];
  char *command;
  int done = 0;
  
  course_element *ce;
  student_element *se;
  
  char *course_key;
  char *student_key;
  
  // initialize dictionaries
  create(&CourseDict, 20);
  create(&StudentDict, 20);

  // process input
  return 0;
}
