
void test_cos_Phi()
{
    
}

void test_cos_theta()
{
     std::cout<<compute_cos_theta(35/180*M_PI, 45*M_PI/180, 10*M_PI/180, 23.35*M_PI/180, 30*M_PI/180);
     theta = 39,72


     root [7] compute_cos_theta(35/180*M_PI, 45*M_PI/180, 10*M_PI/180, 23.35*M_PI/180, 30*M_PI/180);
root [8] std::cout<<compute_cos_theta(35/180*M_PI, 45*M_PI/180, 10*M_PI/180, 23.35*M_PI/180, 30*M_PI/180);
0.342584
root [9] std::cout<<acos(0.342584);
1.22113
root [10] std::cout<<acos(0.342584)*180/M_PI;
69.9656
root [11] std::cout<<compute_cos_theta(35*M_PI/180, 45*M_PI/180, 10*M_PI/180, 23.35*M_PI/180, 30*M_PI/180);
0.769149
root [12] std::cout<<acos(0.769149)*180/M_PI;
39.7225 <- corretto!!!
root [13] 
}