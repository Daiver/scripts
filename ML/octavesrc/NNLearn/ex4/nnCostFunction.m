function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%



A1 = [ones(m, 1) X];

A2 = sigmoid(A1 * Theta1');

A2 = [ones(m, 1) A2];

A3 = sigmoid(A2 * Theta2');

h = A3;

K = num_labels;

n_y = eye(K)(y, :);%dodge ears from one github's user

cst = ( -n_y .* log(h)) - (1 - n_y) .* log(1 - h);

J = 1/m * sum(cst(:));

%dont forget :(


Delta1 = 0;
Delta2 = 0;

for t = 1:m
	A1 = [1 ;X(t, :)'];%start comp activation for this lvl

	Z1 = Theta1 * A1;

	A2 = sigmoid(Z1);

	A2 = [1 ; A2];

	Z2 = Theta2 * A2;

	A3 = sigmoid(Z2);%finish activation

	act = y(t, :);%ansewers for this training set
	y_k = zeros(num_labels, 1);
	y_k(act) = 1;%

	%layer 3 
	delta3 = A3 - y_k;

	Delta2 = Delta2 + (delta3 * A2');

	%layer 2
	delta2 = (Theta2(:, 2:end)' * delta3) .* sigmoidGradient(Z1);
	Delta1 = Delta1 + (delta2 * A1');

end


Theta1_reg = Theta1(:, 2:end);
Theta2_reg = Theta2(:, 2:end);

reg_term = (lambda/(2*m)) * (sumsq(Theta1_reg(:)) + sumsq(Theta2_reg(:)));

J = J + reg_term;

Theta1_grad = (1/m) * Delta1;
Theta2_grad = (1/m) * Delta2;


reg_term1 = (lambda/m) * Theta1(:, 2:end);
Theta1_grad(:, 2:end) = Theta1_grad(:, 2:end) + reg_term1;

reg_term2 = (lambda/m) * Theta2(:, 2:end);
Theta2_grad(:, 2:end) = Theta2_grad(:, 2:end) + reg_term2;



% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
