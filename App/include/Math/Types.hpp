#pragma once

#include <Eigen/Dense>

namespace Spice {
	class Matrix {
	private:
		Eigen::MatrixXd mat;
	public:
		Matrix(int rows, int columns) : mat(rows, columns) { mat.setZero(); } 

		//Fill matrix with zeros
		void setZero() { mat.setZero(); }

		//Add conductance to matrix node
		void add(int nodeA, int nodeB, double conductance) {
			//NODE 0 IS RESERVED FOR GND
			int row = nodeA - 1; 
			int column = nodeB - 1;

			if (row >= 0) mat(row, row) += conductance;
			if (column >= 0) mat(column, column) += conductance;
			if (row >= 0 && column >= 0) {
				mat(row, column) -= conductance;
				mat(column, row) -= conductance;
			}
		}

		//Return raw matrix
		Eigen::MatrixXd& rawMatrix() {return mat;}

	};
	
	class Vector {
	private:
		Eigen::VectorXd vec;
	public:
		Vector(int rows) : vec(rows) { vec.setZero(); }

		//Fill vector with zeros
		void setZero() { vec.setZero(); }

		//Add value to vector
		void add(int node, double val) {

			//NODE 0 RESERVED FOR GROUND
			int index = node - 1;
			if (index >= 0) {
				vec(index) += val;
			}
		}

		Vector solve(Matrix& conductanceMatrix) {
			Vector result(vec.size());
			result.setZero();

			//solver
			result.vec = conductanceMatrix.rawMatrix().ldlt().solve(vec);
			return result;
		}

		double getVoltage(int node) const {
			int index = node - 1;
			if (index >= 0) return vec(index);
			else return 0.0;
		}
	};

}