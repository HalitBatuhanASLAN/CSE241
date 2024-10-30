                                            Matrix2D Class Project
This project implements a Matrix2D class that models a two-dimensional matrix using a vector of vectors. The class supports various matrix operations, including addition, negation, and equality comparison. The program is designed to handle error cases and adheres to object-oriented programming principles.

                                            Class Details
Matrix2D Class

The Matrix2D class represents a 2D matrix with integer elements and includes functionality to:

*Create a matrix with specified dimensions.

*Set and get individual elements in the matrix.

*Perform matrix addition and negation.

*Compare two matrices for equality.

                                            Public Methods
Constructor:

Matrix2D(int line, int column) – Initializes a matrix with the given number of rows (line) and columns (column). All elements are set to zero initially.

Accessors:

-int getLine() – Returns the number of rows in the matrix.

-int getColumn() – Returns the number of columns in the matrix.

-int getElement(int line, int column) – Returns the element at the specified position. Checks if the position is valid before returning.

Modifiers:

-void setElements(int line, int column, int element) – Sets the element at the specified position. Validates the position before setting the value.

Operator Overloading:

-Matrix2D operator+(Matrix2D& mat) const – Adds two matrices of the same size.

-Matrix2D operator-() const – Returns the negation of the matrix.

-bool operator==(Matrix2D& mat) const – Checks if two matrices are equal.

Friend Functions:

-ostream& operator<<(ostream& out, const Matrix2D& m) – Overloads the << operator for easy matrix printing.

Private Helper Functions
-bool isValid(int line, int column) const – Checks if the given indices are within bounds.
bool areSameSize(Matrix2D& other) const – Checks if two matrices have the same dimensions.
