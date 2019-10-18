#include <stdio.h>//For standard IO
#include <stdlib.h>//For rand function
#include <time.h>//To set seed for rand function
#include <math.h>//For exponential function
#define CONVERGENCE_LIMIT 100
#define LEARNING_RATE 0.5
int binary_activation_function(float n)//Computes f(x) where x is the activation value.
{
  return (n>=0?1:0);
}
float sigmoid_activation(float n)//Non linear activation function
{
  return (1/(1-exp(n)));
}
float weight_change() //Returns the error
{

}
void initialize_weights(float w_arr[],int n)//Initializes the weight vector
{
  srand(time(NULL));
  int i;
  for(i=0;i<n;i++)
    w_arr[i]=(rand()%2)-1;//To generate between -1 and 1*/
}
int estimate_value(float i_arr[],float w_arr[],int n)//Computes the value of f(x) based on values of x vector and the weight vector
{
  float val=0.0;
  int i;
  for(i=0;i<n;i++)
    val=val+(i_arr[i]*w_arr[i]);//Computes the sum of products of weights and inputs
  int y=binary_activation_function(val);
  return y;
}
void run_perceptron(float inputs[4][2],float targets[4])//Runs the perceptron by initializing weights and estimating values
{
  int n=2; //Number of weights
  float weights[2];
  initialize_weights(weights,n);
  float prediction=0.0,error=0.0,overall_error=0.0;
  int i=0;
  while(1)
    {
      error=0.0;
      overall_error=0.0;
      float weight_change[4][2]={{0,0},{0,0},{0,0},{0,0}};
      for(i=0;i<4;i++)
	{
	  float ip_set[2]={inputs[i][0],inputs[i][1]};
	  prediction=estimate_value(ip_set,weights,n);
	  error=targets[i]-prediction;
	  overall_error+=error;
	  weight_change[i][0]=error*inputs[i][0]*LEARNING_RATE;
	  weight_change[i][1]=error*inputs[i][1]*LEARNING_RATE;
	  weights[0]+=weight_change[i][0];
	  weights[1]+=weight_change[i][1];
	}
      overall_error/=4;
      if(overall_error==0)
	break;
      if(abs(weight_change[0][0]-weight_change[3][0])>=CONVERGENCE_LIMIT || abs(weight_change[0][1]-weight_change[3][1])>=CONVERGENCE_LIMIT)
	{
	  printf("Non Converging Weights!!");
	  exit(1);
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
  float inputs[4][2]={{0,0},{0,1},{1,0},{1,1}};//NOR gate inputs
  float targets[4]={1,0,0,0}; //NOR gate targets
  run_perceptron(inputs,targets);
  return 0;
}
