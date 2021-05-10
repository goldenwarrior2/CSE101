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

void delCourse(char *c_key) {
  if (find(&CourseDict, c_key) == NULL) {
    printf("Course does not exist.");
    return;
  }
  node_t* course_del = find(&CourseDict, c_key);
  node_t* head = ((course_value*) (course_del->value))->list;
  node_t* store;
  while (head != NULL) {
    store = head->next;
    drop(head->key, c_key);
    head = store;
  }
  delete(&CourseDict, c_key);
}

void enroll(char *s_key, char *c_key) {
  node_t* student_node;
  node_t* course_node;
  
  //course_value* cval = course_node->value;
  //student_value* sval = student_node->value;
  //sval->list = NULL;

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

  node_t* course_list_head = ((student_value*) (student_node->value))->list;       
  if (findList(course_list_head, c_key) != NULL) {
    printf("Student is already enrolled in this course.");
  }
  
  if (((course_value*) (course_node->value))->num_students < ((course_value*) (course_node->value))->capacity) {
    node_t* new_student = student_node;
    memcpy(new_student->key, s_key, 5);
    new_student->value = student_node->value;
    new_student->next = NULL;
    new_student->prev = NULL;
    insertList(&(((course_value*) (course_node->value))->list), new_student);
    ((course_value*) (course_node->value))->num_students++;
  }

  if (((student_value*) (student_node->value))->num_courses == 2) {
    printf("Student is already enrolled in 2 courses");
    return;
  } else {
    node_t* new_course = course_node;
    memcpy(new_course->key, c_key, 5);
    new_course->value = course_node->value;
    new_course->next = NULL;
    new_course->prev = NULL;
    insertList(&(((student_value*) (student_node->value))->list), new_course);
    ((student_value*) (student_node->value))->num_courses++;
  }

}

void drop(char *s_key, char *c_key) {
  if (find(&CourseDict, c_key) == NULL) {
    printf("Course does not exist.");
    return;
  }
  if (find(&StudentDict, s_key) == NULL) {
    printf("Student does not exist.");
    return;
  }
  
  node_t* student = find(&StudentDict, s_key);
  node_t* course = find(&CourseDict, c_key);
  if (findList(((student_value*) (student->value))->list, c_key) != NULL) {
    node_t* course_del = findList(((student_value*) (student->value))->list, c_key);
    deleteList(&(((student_value*) (student->value))->list), course_del);
    ((student_value*) (student->value))->num_courses--;
    node_t* student_del = findList(((course_value*) (course->value))->list, s_key);
    deleteList(&((course_value*) (course->value))->list, student_del);
    ((course_value*) (course->value))->num_students--;
  }
}

void printStudents() {
  printf("Students: \n");
  print(&StudentDict);
}

void printCourses() {
  printf("Courses: \n");
  print(&CourseDict);
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
  while (!done) {
    fgets(line, 100, stdin);

    command = strtok(line, " \t");
    
    if (strcmp(command, "ex") == 0) {
      printf("Exited Program\n");
      done = 1;
    }
    else if (strcmp(command, "ac") == 0) {
      ce = (course_element *) malloc(sizeof(course_element));
      course_key = strtok(NULL, " ");
      printf("Adding course: %s\n", course_key);
      memcpy((*ce).key, course_key, 5);
      ce->value = (void *) newNode('c');
      ce->value->capacity = atoi(strtok(NULL, " "));
      ce->value->num_students = 0;
      ce->value->list = NULL;
      addCourse(ce);
    }
    else if (strcmp(command, "dc") == 0) {
      course_key = strtok(NULL, " ");
      delCourse(course_key);
      printf("Delete Course Complete\n");
    }
    else if (strcmp(command, "en") == 0) {
      student_key = strtok(NULL, " ");
      course_key = strtok(NULL, " ");
      printf("Enrolling student: %s into course: %s\n", student_key, course_key);
      enroll(student_key, course_key);
    }
    else if (strcmp(command, "dr") == 0) {
      student_key = strtok(NULL, " ");
      course_key = strtok(NULL, " ");
      printf("Dropping student: %s from course: %s\n", student_key, course_key);
      drop(student_key, course_key);
    }
    else if (strcmp(command, "ps") == 0) {
      printStudents();
    }
    else if (strcmp(command, "pc") == 0) {
      printCourses();
    }
    else {
      printf("Unrecognized command: %2s\n", command);
    }
  }
  return 0;
}
