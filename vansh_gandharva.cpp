//Name- Vansh Gandharva (230102102)
#include <bits/stdc++.h> 
using namespace std;

//classes used 
class Polynomial;
class Matrix;

//Stream operator declarations
istream& operator>>(istream& is, Polynomial& p);
ostream& operator<<(ostream& os, const Polynomial& p);

//Task 1: Class Polynomial
class Polynomial {
private:
    int terms;      
    int* coeff;     
    int* degree;    
    //This was added to maintain and sort the degree terms and add similar power terms 
    void maintain() { 
        if (terms <= 0) return;

        vector<pair<int, int>> temp_terms;
        
        for (int i = 0; i < terms; ++i) {
            int current_degree = degree[i];
            int current_coeff = coeff[i];

            if (current_coeff == 0 && terms > 1) continue;

            bool found = false;
            for (auto& term : temp_terms) {
                if (term.second == current_degree) {
                    term.first += current_coeff;
                    found = true;
                    break;
                }
            }
            if (!found) {
                temp_terms.push_back({current_coeff, current_degree});
            }
        }

        sort(temp_terms.begin(), temp_terms.end(), 
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second > b.second;
            });

        delete[] coeff; delete[] degree;

        int new_terms = 0;
        for (const auto& term : temp_terms) {
            if (term.first != 0) new_terms++;
        }

        terms = new_terms > 0 ? new_terms : 1; 
        coeff = new int[terms]();
        degree = new int[terms]();
        
        if (new_terms > 0) {
            int current_idx = 0;
            for (const auto& term : temp_terms) {
                if (term.first != 0) {
                    coeff[current_idx] = term.first;
                    degree[current_idx] = term.second;
                    current_idx++;
                }
            }
        }
    }

public: 
    //Default Constructor
    Polynomial(int numTerms = 3) : terms(numTerms), coeff(nullptr), degree(nullptr) {
        if (terms > 0) {
            coeff = new int[terms]();
            degree = new int[terms]();
        }
    }
    //Parameterized Constructor
    Polynomial(int* c_ptr, int* d_ptr, int numTerms) : terms(numTerms), coeff(nullptr), degree(nullptr) {
        if (terms > 0) {
            coeff = new int[terms];
            degree = new int[terms];
            for (int i = 0; i < terms; ++i) {
                coeff[i] = c_ptr[i];
                degree[i] = d_ptr[i];
            }
            maintain(); 
        }
    }
    //Destructor
    ~Polynomial() {
        delete[] coeff;
        delete[] degree;
    }
    //Deep Copy Constructor 
    Polynomial(const Polynomial& other) : terms(other.terms), coeff(nullptr), degree(nullptr) { 
        if (terms > 0) {
            coeff = new int[terms]; degree = new int[terms];
            for (int i = 0; i < terms; ++i) { coeff[i] = other.coeff[i]; degree[i] = other.degree[i]; }
        }
    }
    Polynomial& operator=(const Polynomial& other) { 
        if (this != &other) {
            delete[] coeff; delete[] degree; terms = other.terms; coeff = nullptr; degree = nullptr;
            if (terms > 0) {
                coeff = new int[terms]; degree = new int[terms];
                for (int i = 0; i < terms; ++i) { coeff[i] = other.coeff[i]; degree[i] = other.degree[i]; }
            }
        }
        return *this;
    }
    //Overloaded >> operator(Stream Extraction)
    friend istream& operator>>(istream& is, Polynomial& p) {
        delete[] p.coeff; delete[] p.degree;

        if (p.terms > 0) {
            p.coeff = new int[p.terms]; p.degree = new int[p.terms];
            for (int i = 0; i < p.terms; ++i) {
                if (!(is >> p.coeff[i] >> p.degree[i])) break;
            }
        }
        //To convert the polynomial into standard form
        p.maintain(); 
        return is;
    }

    //Overloaded << operator (Stream Insertion)
    friend ostream& operator<<(ostream& os, const Polynomial& p) {
        bool first_term = true;
        for (int i = 0; i < p.terms; ++i) {
            if (p.coeff[i] != 0 || p.terms == 1) { 
                if (!first_term) os << " + ";
                os << p.coeff[i] << "x^" << p.degree[i];
                first_term = false;
            }
        }
        if (first_term) os << "0x^0";
        return os;
    }

    //Overloaded + operator (Addition) 
    Polynomial operator+(const Polynomial& other) const {
        int max_terms = terms + other.terms;
        int* result_coeff = new int[max_terms];
        int* result_degree = new int[max_terms];
        int k = 0;

        for (int i = 0; i < terms; ++i) { result_coeff[k] = coeff[i]; result_degree[k] = degree[i]; k++; }
        for (int i = 0; i < other.terms; ++i) { result_coeff[k] = other.coeff[i]; result_degree[k] = other.degree[i]; k++; }

        Polynomial result(result_coeff, result_degree, k);
        delete[] result_coeff; delete[] result_degree;
        return result;
    }

    //Overloaded - operator (Subtraction) 
    Polynomial operator-(const Polynomial& other) const {
        int max_terms = terms + other.terms;
        int* result_coeff = new int[max_terms];
        int* result_degree = new int[max_terms];
        int k = 0;

        for (int i = 0; i < terms; ++i) { result_coeff[k] = coeff[i]; result_degree[k] = degree[i]; k++; }
        for (int i = 0; i < other.terms; ++i) { result_coeff[k] = -other.coeff[i]; result_degree[k] = other.degree[i]; k++; }

        Polynomial result(result_coeff, result_degree, k);
        delete[] result_coeff; delete[] result_degree;
        return result;
    }

    //Overloaded * operator (Multiplication) 
    Polynomial operator*(const Polynomial& other) const {
        int max_terms = terms * other.terms;
        int* result_coeff = new int[max_terms];
        int* result_degree = new int[max_terms];
        int k = 0;

        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < other.terms; ++j) {
                result_coeff[k] = coeff[i] * other.coeff[j];
                result_degree[k] = degree[i] + other.degree[j];
                k++;
            }
        }
        
        Polynomial result(result_coeff, result_degree, k);
        delete[] result_coeff; delete[] result_degree;
        return result;
    }
};

//Task 2: Class Matrix
class Matrix {
private:
    int rows;
    int columns;
    Polynomial** p_matrix;

public:
    //Constructor 
    Matrix(int r = 2, int c = 2) : rows(r), columns(c), p_matrix(nullptr) {
        if (rows > 0 && columns > 0) {
            p_matrix = new Polynomial*[rows];
            for (int i = 0; i < rows; ++i) {
                p_matrix[i] = new Polynomial[columns];
            }
        }
    }
    //Destructor 
    ~Matrix() {
        if (p_matrix) {
            for (int i = 0; i < rows; ++i) delete[] p_matrix[i];
            delete[] p_matrix;
        }
    }
    //Overloaded << operator 
    friend ostream& operator<<(ostream& os, const Matrix& M) {
        for (int i = 0; i < M.rows; ++i) {
            os << "| ";
            for (int j = 0; j < M.columns; ++j) {
                os << M.p_matrix[i][j];
                if (j < M.columns - 1) os << "\t\t";
            }
            os << " |\n";
        }
        return os;
    }
    //Overloaded [] operator
    Polynomial* operator[](int index) {
        return p_matrix[index];
    }
    //Overloaded + operator (Addition) 
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) throw invalid_argument("Error in Matrix addition: Dimensions not matching.");
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result.p_matrix[i][j] = p_matrix[i][j] + other.p_matrix[i][j];
            }
        }
        return result;
    }
    //Overloaded - operator (Subtraction) 
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || columns != other.columns) throw invalid_argument("Error in Matrix subtraction: Dimensions not matching.");
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                result.p_matrix[i][j] = p_matrix[i][j] - other.p_matrix[i][j];
            }
        }
        return result;
    }
    //Overloaded * operator (Multiplication) 
    Matrix operator*(const Matrix& other) const {
        if (columns != other.rows) throw invalid_argument("Error in Matrix multiplication: A columns must be equal to B rows.");

        Matrix result(rows, other.columns);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.columns; ++j) {
                
                Polynomial sum(1); 
                
                for (int k = 0; k < columns; ++k) {
                    sum = sum + (p_matrix[i][k] * other.p_matrix[k][j]);
                }
                result.p_matrix[i][j] = sum;
            }
        }
        return result;
    }
};

//Task 3:Main funtion
void run_code(const string& filename) {
    //Use ifstream to read directly from the input file.
    ifstream inputFile(filename); 
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file " << filename << endl;
        return;
    }
    istream& input_stream = inputFile; 

    int num_poly, poly_terms, rows, cols;
    //Read the number of polynomials
    if (!(input_stream >> num_poly >> poly_terms)) { 
        cerr << "Error reading num_poly and poly_terms." << endl;
        return;
    }
    //Read number of rows and number of columns 
    if (!(input_stream >> rows >> cols)) {
        cerr << "Error reading rows and cols." << endl;
        return;
    }
    
    cout << "***** Assignment by Vansh Gandharva *****\n";
    cout << "File name : " << filename << endl;
    cout << "Matrix Size : " << rows << "x" << cols << "\n";

    //Declaring 2d arrays m1 & m2 of matrix objects
    Matrix m1(rows, cols);
    cout << "\nMatrix A:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //Read each polynomial into a separate polynomial object 
            Polynomial P_temp(poly_terms);
            input_stream >> P_temp; 
            //Assign the polynomial to each element of m1 
            m1[i][j] = P_temp;
        }
    }
    cout << m1;
 
    Matrix m2(rows, cols);
    cout << "\nMatrix B:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Polynomial P_temp(poly_terms);
            input_stream >> P_temp; 
            m2[i][j] = P_temp;
        }
    }
    cout << m2;
    inputFile.close(); 
    
    //Final operations
    //Used try and catch to check for errors
    try {
        cout << "\nA + B --->\n";
        cout << (m1 + m2);
        cout << "\nA - B --->\n";
        cout << (m1 - m2);
        cout << "\nA * B --->\n";
        cout << (m1 * m2);    
    } catch (const invalid_argument& e) {
        cerr << "\nMatrix Error: " << e.what() << endl;
    }
}

int main() {
    //The input file name should be passed here.
    run_code("input-02.txt");
    return 0;
}