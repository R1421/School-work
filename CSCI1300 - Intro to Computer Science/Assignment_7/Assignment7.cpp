#include<iostream>
#include<unistd.h>
#include<random>
#include<chrono>
#include<cstdlib>
#include<math.h>

using namespace std;

/* The following function takes in the values entered in the terminal and uses them to find the passer rating of a player
The needed values are:
    Pass Completions    Comp
    Pass Attempts       Att
    Passing yards       Yds
    Touchdowns          Tds
    Interceptions       Its
And the output is a double which represents the skill of the player and a rating of said player*/
void PasserRating(double Comp, double Att, double Yds, double Tds, double Its)
{
    double C = ((Comp/Att) - .3)*5;
    double Y = ((Yds/Att) - 3)*.25;
    double T = (Tds/Att) * 20;
    double I = 2.375 - ((Its/Att)*25);
    cout<<C<<endl<<Y<<endl<<T<<endl<<I<<endl;


    //The next few sets of if statements change the numbers if they are too low or too high
    if (C<0)
        C = 0;
    if (Y<0)
        Y = 0;
    if (T<0)
        T = 0;
    if (I<0)
        I = 0;

    if (C>2.375)
        C = 2.375;
    if (Y>2.375)
        Y = 2.375;
    if (T>2.375)
        T = 2.375;
    if (I>2.375)
        I = 2.375;
    cout<<C<<endl<<Y<<endl<<T<<endl<<I<<endl;

    //This is the actual calculation of the rating of the player
    double Rating = (C+Y+T+I)/6*100;

    //The following conditional block will determine whether the rating is bad or good
    if (Rating < 85)
        cout<<"Rating "<<Rating<<" this is poor"<<endl;
    if (Rating >= 85 && Rating < 90)
        cout<<"Rating "<<Rating<<" this is mediocre"<<endl;
    if (Rating >= 90 && Rating < 95)
        cout<<"Rating "<<Rating<<" this is good"<<endl;
    if (Rating >= 95)
        cout<<"Rating "<<Rating<<" this is great"<<endl;
}

/*The next function takes some values and outputs the power needed from a cyclist to overcome air and friction resistance
The following values are the variables in the function:
    Rider Mass                      rMass
    Bike mass                       bMass
    velocity                        v
    gravity                         g
    position coefficient            k
    rolling friction coefficient    fricR
    drag coefficient                fricD
    distance (in km)                d
*/
void PowerEnergy(double rMass, double bMass, double v, double d)
{
    //First, we need to calculate the total air resistance using the inputed variables after setting the constants
    double g = 9.8;
    double k = .18;
    double fricR = .001;

    //The following is a part of the function which finds the time required to travel given distance at a given velocity
    double time = (d*1000)/v;
    //It is used to find the total energy expended
    /* In order to simulate real world conditions, we will generate random values for the coefficient of friction
    In order to do this, we need to use the built in random_device class*/
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution <double> distribution (0.5, 1.0);
    double energy = 0;
    int iteration = time/60;

    for (int i = 0; i < iteration; i++)
    {
        //cout<<distribution(generator)<<endl;
        double fricD = distribution(generator);
        cout<<fricD<<endl;
        //pRoll is the power to overcome rolling friction
        double pRoll = fricR * g * (rMass + bMass)*v;
        //pAir is the power needed to overcome drag
        double pAir = k * fricD * v*v*v;

        //P is the total power needed
        double P = pRoll + pAir;

        energy += P*60;
    }
    cout<<energy<<endl;

    //Calculate the average energy per minute
    int averageEnergy = energy/iteration;
    cout<<averageEnergy<<endl;

}

int main(int argc, char *argv[])
{
    int x;
    bool football = false;
    bool cycling = false;
    double m;
    double b;
    double v;
    double d;
    double p;
    double a;
    double y;
    double t;
    double i;
    while ((x = getopt (argc, argv, "fcm:b:v:d:p:a:y:t:i:")) != -1)
    {

        if (x == 'f')
            football = true;
        if (x == 'c')
            cycling = true;
        if (x == 'm')
            m = atof(optarg);
        if (x == 'b')
            b = atof(optarg);
        if (x == 'v')
            v = atof(optarg);
        if (x == 'd')
            d = atof(optarg);
        if (x == 'p')
            p = atof(optarg);
        if (x == 'a')
            a = atof(optarg);
        if (x == 'y')
            y = atof(optarg);
        if (x == 't')
            t = atof(optarg);
        if (x == 'i')
            i = atof(optarg);

    }
    //cout<<m<<endl<<b<<endl<<v<<endl<<d<<endl;

    //Now that all the flags should have been checked, create conditionals to say which functions run
    if (football)
        PasserRating(p,a,y,t,i);
    if (cycling)
        PowerEnergy(m,b,v,d);

}
