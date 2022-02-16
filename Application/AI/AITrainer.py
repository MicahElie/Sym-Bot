import numpy as np


class AITrainer:

    def __init__(self, n, k):
        self.N = n  # Number of parameters (including constant term)
        self.K = k  # Number of possible actions
        self.M = 0  # Number of training examples
        self.Theta = np.zeros((n, k))  # One-vs-all: One set of thetas for every class (action)
        self.X = np.zeros((1, n))
        self.Y = np.zeros((1, k))

    def sigmoid(self, Z):
        # for row in range(self.M):
        #    for col in range(self.K):
        #       Z[row, col] = 1 / (1 + math.exp(-Z[row, col]))

        return 1 / (1 + np.exp(-Z))

    def cost_function(self):
        J = 1/self.M*np.sum(-self.Y*np.log(self.sigmoid(np.dot(self.X, self.Theta))) *
                            (1-self.Y)*np.log(1-self.sigmoid(np.dot(self.X, self.Theta))), 0)
        grad = 1/self.M*np.dot(self.X.T, (self.sigmoid(np.dot(self.X, self.Theta))-self.Y))
        return J, grad

    def cost_function_reg(self, lambda_):
        cost = self.cost_function()
        theta = np.vstack(np.array([0]*self.K), self.Theta[1:self.N, :])

        J = cost[0] + lambda_/(2*self.M)*sum(theta*theta, 0)
        grad = cost[1] + lambda_/self.M*theta
        return J, grad

    def grad_descent(self, theta_0, alpha, lambda_):
        self.Theta = theta_0
        cost = self.cost_function_reg(lambda_)
        delta = np.ones((1, self.K))
        self.Theta = self.Theta - alpha*cost[1]*cost[0]
        while np.any(delta > 1e-3):
            cost_ = self.cost_function_reg(lambda_)
            delta = np.abs(cost_[0] - cost[0])
            cost = cost_
            self.Theta = self.Theta - alpha*cost[1]*cost[0]

    def read_data(self, filename):
        with open(filename) as file:
            for line in file:
                if line[0] != '#':
                    self.add_training_example(line)
        self.Y = self.Y[1:, :]
        self.X = self.X[1:, :]

    def add_training_example(self, line):
        data = line.split()

        y_ = [0]*self.K
        y_[int(data[0])] = 1
        self.Y = np.vstack((self.Y, np.array(y_)))

        x_ = [1]
        x_.extend([float(f) for f in (data[1:])])
        self.X = np.vstack((self.X, np.array(x_)))

        self.M = self.M + 1



