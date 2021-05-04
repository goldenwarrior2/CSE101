// -----------------------------
// Enrollment structs
// -----------------------------

typedef struct {
	int	capacity;		// course capacity
	int	num_students;	// number of students enrolled
	node_t	*list;		// list of students in course
	} course_value;

typedef struct {
	int	num_courses;	// number of courses enrolled in
	node_t	*list;		// list of courses student is enrolled in
	} student_value;

typedef struct {		// key:value pair for a course
	char		key[5];
	course_value	*value;
	} course_element;

typedef struct {		// key:value pair for a student
	char		key[5];
	student_value	*value;
	} student_element;
