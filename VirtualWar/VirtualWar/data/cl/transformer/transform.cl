
void kernel transform(global const float* vecStream,global const float*mat ,global float * outStream,int count)
{
   
    int i = get_global_id(0);

    int vS = i * 3;

    //printf("Count:%d\n",count);
    //printf("vs:%d\n",vS);


    outStream[i] = vecStream[i];



}