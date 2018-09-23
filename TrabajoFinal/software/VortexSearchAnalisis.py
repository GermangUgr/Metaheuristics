from __future__ import division
import scipy.special as S
import numpy as np
import optproblems.cec2005 as opt_prob

def limit_variables(C, upperlimit, lowerlimit):

	return [np.random.uniform(0,1) * (upperlimit - lowerlimit) + lowerlimit if c > upperlimit or c < lowerlimit else c for c in C]


def vortex_search(function, psize, max_iters, id):

	np.random.seed(3)

	#get optimization problem parameters
	upperlimit = function.max_bounds[0]
	lowerlimit = function.min_bounds[0]
	dimension = function.num_variables 

	file = open("./results/best_value_" + str(id) + "_dim" + str(dimension) + ".dat", "w")

	mu = 0.5 * (upperlimit + lowerlimit);
	center = np.full(dimension, mu)

	global_min_value = np.inf

	x = 0.1 #x = 0.1 for gammaincinv(x,a) function

	ginv = (1/x)*S.gammaincinv(x,(max_iters - 1)/max_iters) # compute ginv value

	r = ginv * ((upperlimit - lowerlimit) / 2) # initial radius of the circle

	count = max_iters #itr counter

	# print("ginv: ", ginv, " r: ", r, " count: ", count)

	while (count > 0):

		#generate candidate solutions around (0,0) using gaussian distribution
		# C = np.array([np.random.normal(0, 1, dimension)*r for i in xrange(1, psize)])
		#generate candidate solutions around (0,0) using an uniform distribution
		C = np.array([-r + 2*r * np.random.normal(0, 1, dimension) for i in xrange(1, psize)])

		#displace candidates around the actual center
		Cs = C + center

		#limit variables
		Cs = [limit_variables(c, upperlimit, lowerlimit) for c in Cs]

		#evaluate all candidate solutions
		evals = [function(c) for c in Cs]

		#find best solution index
		best_index = evals.index(min(evals))

		#update best solution so far if needed
		if evals[best_index] < global_min_value :
			global_min_value = evals[best_index]
			global_min_sol = Cs[best_index]

		#center is always shifted to the best solution found so far
		center = global_min_sol
		#decrease iter counter
		count = count - 1

		#radius decrement process
		a = count / max_iters # a value for gammaincinv function
		ginv = (1/0.1)*S.gammaincinv(0.1,a) # compute the new ginv value
		r = ginv * ((upperlimit - lowerlimit) / 2) # decrease the radius

		file.write("{} {} \n".format((max_iters-count)*psize, global_min_value))

	file.close()

	return [global_min_value, global_min_sol]	    


def main():

	psize = 50
	max_evals = 10000

	for dim in [30]:

		print("##################################### DIMENSION: " + str(dim) + " #####################################")
		print("Valor obtenido | Optimo | Desviacion")
		print "######### Funcion 1: Shifted sphere #########"
		func = opt_prob.F1(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 1)
		print("F1 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 2: Shifted double-sum #########"
		func = opt_prob.F2(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 2)
		print("F2 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))	
		print "######### Funcion 5: Schewfels Problem with Global Optimum on Bounds #########"
		func = opt_prob.F5(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 5)
		print("F5 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 6: Shifted Rosenbrocks function #########"
		func = opt_prob.F6(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 6)
		print("F6 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 8: Shifted rotated Ackleys function with global optimum on bounds #########"
		func = opt_prob.F8(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 8)
		print("F8 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 9: Shifted Rastrigins function #########"
		func = opt_prob.F9(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 9)
		print("F9 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 10: Shifted rotated Rastrigins function #########"
		func = opt_prob.F10(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 10)
		print("F10 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 11: Shifted rotated Weierstrass function #########"
		func = opt_prob.F11(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 11)
		print("F11 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 13: Rosenbrocks function #########"
		func = opt_prob.F13(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 13)
		print("F13 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 14: Shifted rotated expanded Schaffers F6 #########"
		func = opt_prob.F14(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 14)
		print("F14 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 17: Rotated hybrid composition function F16 with noise #########"
		func = opt_prob.F17(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 17)
		print("F17 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 22: Rotated hybrid composition function F21 with high condition number matrix. #########"
		func = opt_prob.F22(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 22)
		print("F22 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))
		print "######### Funcion 24: Rotated hybrid composition function F24 #########"
		func = opt_prob.F24(dim)
		[value,vector] = vortex_search(func, psize, 1000*dim, 24)
		print("F24 & {} & {} & {}".format(value, func.bias, np.round(np.absolute((value - func.bias) / func.bias * 100), 4) ))


if __name__ == "__main__": main()


			
		