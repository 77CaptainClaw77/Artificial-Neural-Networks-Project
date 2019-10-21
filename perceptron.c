#include <stdio.h>//For standard IO
#include <stdlib.h>//For rand function
#include <time.h>//To set seed for rand function
#include <math.h>//For exponential function
#define CONVERGENCE_LIMIT 100 //To stop training if weight change diverges beyond limit
#define LEARNING_RATE 0.5 //Learning Rate Parameter for Perceptron Learning Law
#define MAX_ITERATIONS 100000 //Maximum number of iterations allowed to prevent infinite loop 
float threshold=0.0;
int binary_activation_function(float n)//Computes f(x) where x is the activation value.
{
  return (n>=threshold?1:0);
}
float sigmoid_activation(float n)//Non linear activation function
{
  return (1/(1+exp(-n)));
}
void initialize_weights(float w_arr[],int n)//Initializes the weight vector
{
  srand(time(NULL));
  int i;
  for(i=0;i<n;i++)
    w_arr[i]=0;
    //w_arr[i]=(rand()/((float)RAND_MAX/3.0))-1;//To generate between -1 and 1
}
int estimate_value(float i_arr[],float w_arr[],int n)//Computes the value of f(x) based on values of x vector and the weight vector
{
  float val=0.0;
  int i;
  for(i=0;i<n;i++)
    val=val+(i_arr[i]*w_arr[i]);//Computes the sum of products of weights and inputs
  int y=binary_activation_function(val);
  //int y=round(sigmoid_activation(val)); Uncomment to use sigmoid activation function instead.
  return y;
}
void run_perceptron(float** inputs,float* targets,int no_of_inputs,int input_size)//Runs the perceptron by initializing weights and estimating values
{
  int n=input_size;
  float weights[2];
  initialize_weights(weights,n);
  float prediction=0.0,error=0.0,overall_error=0.0,initial_weight_change=0.0;
  int i=0,j=0;
  int iter_count=0;
  int first_iteration=1; //Boolean variable to check for the first iteration
  while(1)
    {
      error=0.0;
      overall_error=0.0;
      float weight_change[no_of_inputs][n];
      for(i=0;i<no_of_inputs;i++)
	for(j=0;j<n;j++)
	  weight_change[i][j]=0; //Initialising weight change to 0.
      for(i=0;i<no_of_inputs;i++)
	{
	  float ip_set[input_size];
	  for(j=0;j<input_size;j++)
	    ip_set[j]=inputs[i][j];//Build current input set for value estimation
	  prediction=estimate_value(ip_set,weights,n); //Output produced by the neuron
	  error=targets[i]-prediction; 
	  overall_error+=error;
	  for(j=0;j<input_size;j++)
	    {
	      weight_change[i][j]=error*inputs[i][j]*LEARNING_RATE;
	      weights[j]+=weight_change[i][j];
	    }
	  iter_count++;
	  if(first_iteration)
	    {
	      int k;
	      for(k=0;k<no_of_inputs;k++)
		for(j=0;j<n;j++)
		  initial_weight_change+=weight_change[k][j];
	      initial_weight_change=initial_weight_change/(no_of_inputs*n);
	      first_iteration=0;
	    }
	}
      overall_error/=4;
      float overall_change=0.0;
      for(i=0;i<no_of_inputs;i++)
	for(j=0;j<input_size;j++)
	  overall_change+=weight_change[i][j];
      overall_change/=(no_of_inputs*n);
      if(abs(overall_change-initial_weight_change)>CONVERGENCE_LIMIT)
	{
	  printf("Weights do not converge!");
	  exit(1);
	}
      if(overall_error==0)
	break;
      if(iter_count>MAX_ITERATIONS)
	{
	  printf("Exiting due to iteration count being exceeded!");
	  break;
	}
    }
  printf("\nWeight 1: %f\tWeights 2: %f",weights[0],weights[1]);
  for(i=0;i<4;i++)
    {
       float ip_set[2]={inputs[i][0],inputs[i][1]};
       prediction=estimate_value(ip_set,weights,n);
       printf("\n %f %f -> %f",inputs[i][0],inputs[i][1],prediction);
    }
}
int main()
{
  //run_perceptron();
  printf("Implementation Of NOR Gate using Perceptron Neuron Model\n");
  printf("Enter the number of input sets: ");
  int n,m,i,j;
  scanf("%d",&n);
  printf("Enter the size of each input set: ");
  scanf("%d",&m);
  float** inputs=malloc(sizeof(float*)*n);
  for(i=0;i<n;i++) inputs[i]=malloc(sizeof(float)*m);
  printf("Enter the input set along with the desired output in the form:- input1 intput2... output\n");
  float* targets=malloc(sizeof(float)*n);
  for(i=0;i<n;i++)
    {
      for(j=0;j<m;j++)
	scanf("%f",&inputs[i][j]);
      scanf("%f",&targets[i]);
    }
  char ch;
  printf("Enter \'y\' if NOR gate inputs are entered else press any other key :");
  scanf("%*c%c",&ch);
  if(ch!='y')
    {
      printf("Enter the threshold value:");
      scanf("%f",&threshold);
    }
  run_perceptron(inputs,targets,4,2);
  return 0;
}
