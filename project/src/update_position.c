#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<openmp.h>

struct ibody {
  float mass;
  float x_pos;
  float y_pos;
  float x_vel;
  float y_vel;
  float radius;
};

struct volume {
    size_t size;
    size_t last;
    size_t current;
    struct ibody** objects;
};

void volume_append(struct volume* v, struct ibody* ib) {
    if( v->last == v->size ) {
        (v->size) += 100;
        v->objects = realloc(v->objects, sizeof(struct ibody*)*(v->size)+100);
    }
    (v->objects)[(v->last)] = ib;
    (v->last) += 1;
    return;
}

void parseLine(char* line, char** fields) {
  fields[0] = strtok(line, ",");
  for(int i = 1; i < 6; i ++) {
    fields[i] = strtok(NULL, ",");
  }
  return;
}

void calculate_centroid(struct volume* v, float* cx, float* cy, float* ms) {
    double mass_sum=0.0;
    double wx=0.0;
    double wy=0.0;
    for(int i=0; i<v->last; i++) {
      if(i != v->current) {
        struct ibody* ib = v->objects[i];
        mass_sum += ib->mass;
        wx += ib->x_pos * ib->mass;
        wy += ib->y_pos * ib->mass;
      }
    }
    *ms = mass_sum;
    *cx = wx/mass_sum;
    *cy = wy/mass_sum;

    return;
}

void update_curr_body(struct ibody* ib, struct volume* out_v, float* cx, float* cy, float* mass_sum, float length_of_timesteps) {
  //update out_v with new values
  float G;
  float object_accel;
  float angleBetween;
  float ax;
  float ay;
  int ax_sign;
  int ay_sign;
  //set up signs
  if(*cx-ib->x_pos < 0) {
    ax_sign = -1;
  }
  else if(*cx-ib->x_pos > 0) {
    ax_sign = 1;
  }
  else {
    ax_sign = 0;
  }

  //set up signs
  if(*cy-ib->y_pos < 0) {
    ay_sign = -1;
  }
  else if(*cy-ib->y_pos > 0) {
    ay_sign = 1;
  }
  else {
    ay_sign = 0;
  }
  struct ibody* add_b = malloc(sizeof(struct ibody*));
  object_accel = (2**mass_sum)/(pow(*cx - ib->x_pos,2)+pow(*cy-ib->y_pos,2));
  if(*cx-ib->x_pos != 0.0)
  {
    angleBetween = atan(fabs(*cy-ib->y_pos)/fabs(*cx-ib->x_pos));
  }
  else {
    angleBetween=0;
  }
  ax = ax_sign*object_accel*cos(angleBetween);
  ay = ay_sign*object_accel*sin(angleBetween);
  //create updated ibody
  add_b->mass = ib->mass;
  add_b->x_pos = ib->x_pos + .5*ib->x_vel*length_of_timesteps + .5*ax*pow(length_of_timesteps,2);
  add_b->y_pos = ib-> y_pos + .5*ib->y_vel*length_of_timesteps + .5*ay*pow(length_of_timesteps,2);
  add_b->x_vel = ib->x_vel + ax*length_of_timesteps;
  add_b->y_vel = ib->y_vel + ay*length_of_timesteps;
  add_b->radius = ib->radius;
  volume_append(out_v, add_b);
  return;
}

void writetoFile(struct volume* out, int timestep) {
  FILE* fw;
  char* fname = malloc(sizeof(char)*100);
  sprintf(fname, "./data/%d.txt",timestep);
  fw = fopen(fname,"w+");
  fprintf(fw, "Mass,x_pos,y_pos,x_vel,y_vel,radius\n%d \n",timestep);
  for(int i = 0; i < out->last; i++) {
    fprintf(fw, "%f,%f,%f,%f,%f,%f\n",out->objects[i]->mass,out->objects[i]->x_pos,out->objects[i]->y_pos,out->objects[i]->x_vel,out->objects[i]->y_vel,out->objects[i]->radius);
  }
  free(fname);
  return;
}

int main(int argc, char** argv) {

  //usage
  if(argc < 4 ) {
    printf("usage: <string> input_filname <int> num_of_timesteps <int> length_of_timesteps");
  }
  //ibody setup
  struct volume in_v;
  in_v.size=100;
  in_v.last=0;
  in_v.current = 0;
  in_v.objects = malloc(sizeof(struct ibody*)*100);

  struct volume out_v;
  out_v.size=100;
  out_v.last=0;
  out_v.current=0;
  out_v.objects = malloc(sizeof(struct ibody*)*100);

  //file read setup
  FILE* f;
  char * line = 0;
  size_t len = 0;
  ssize_t read;

  //forstrtol error handling
  char* err_ptr;

  //open file set up ibodies
  f = fopen(argv[1], "r");

  //throw away header
  getline(&line, &len, f);
  getline(&line, &len, f);

  //read lines and parse to ibody struct in in volume struct
  while ((read = getline(&line, &len, f)) != -1) {
    char** fields = malloc(sizeof(char*)*7);
    parseLine(line, fields);
    struct ibody* add_b = malloc(sizeof(struct ibody*));
    add_b->mass = strtol(fields[0],&err_ptr,10);
    add_b->x_pos = strtol(fields[1],&err_ptr,10);
    add_b->y_pos = strtol(fields[2],&err_ptr,10);
    add_b->x_vel = strtol(fields[3],&err_ptr,10);
    add_b->y_vel = strtol(fields[4],&err_ptr,10);
    add_b->radius = strtol(fields[5],&err_ptr,10);
    volume_append(&in_v, add_b);
  }
  fclose(f);

  float cx;
  float cy;
  float mass_sum;

  //for each timestep
  for(int i = 0; i < strtol(argv[2],&err_ptr,10); i++) {
    in_v.current = 0;
    //for each body
    #pragma omp parallel for reduction(+:mass_sum,wx,wy)
    for(int j = 0; j < in_v.last; j++) {
      // printf("%d\n",j);
      cx = 0;
      cy = 0;
      mass_sum = 0;
      calculate_centroid(&in_v, &cx, &cy, &mass_sum);
      update_curr_body(in_v.objects[in_v.current], &out_v, &cx, &cy, &mass_sum, strtof(argv[3],NULL));
      in_v.current++;
    }
    writetoFile(&out_v, i);
    memcpy(&in_v,&out_v,sizeof(out_v));
    out_v.last = 0;
    printf("timestep %d complete\n", i);
  }

  return 0;
}
