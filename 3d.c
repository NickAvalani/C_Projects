/*
Name: Nick Avalani
Course: CSC 352, Fall 2022, Benjamin Dicken
Description: This program  will provide an interface for creating a 3D scene, adding shapes to this scene
(represented via a linked list (ish) data structure), and saving these scenes to .stl files so they can be viewed
in a variety of other software.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3d.h"

Scene3D* Scene3D_create(){
	Scene3D* scene = malloc(sizeof(Scene3D));
	scene->count = 0;
	scene->root = malloc(sizeof(Triangle3DNode));
	scene->root->next = NULL;
	return scene;
}

void Scene3D_destroy(Scene3D* scene){
	Triangle3DNode* curr = scene->root;
	while(curr != NULL){
		Triangle3DNode* next = curr->next;
		free(curr);
		curr = next;
	}
	free(scene);
	return;
}

void Scene3D_write_stl_text(Scene3D* scene, char* file_name){
	FILE* file = fopen(file_name, "w");
	Triangle3DNode* curr = scene->root;
	fprintf(file, "solid scene\n");
	for(int i = 0; i < scene->count; i++){
		if(curr != NULL){
			fprintf(file, "  facet normal 0.0 0.0 0.0\n");
			fprintf(file, "    outer loop\n");
			fprintf(file, "      vertex %0.5lf %0.5lf %0.5lf\n", (curr->triangle).a.x, (curr->triangle).a.y, (curr->triangle).a.z);
 	                fprintf(file, "      vertex %0.5lf %0.5lf %0.5lf\n", (curr->triangle).b.x, (curr->triangle).b.y, (curr->triangle).b.z);
           		fprintf(file, "      vertex %0.5lf %0.5lf %0.5lf\n", (curr->triangle).c.x, (curr->triangle).c.y, (curr->triangle).c.z);
			fprintf(file, "    endloop\n");
			fprintf(file, "  endfacet\n");
			curr = curr -> next;
		}
	}
	fprintf(file, "endsolid scene");
        fclose(file);
        return;
}

/*
This function takes in the scene and a triangle and 
adds the triangle as a node in the linked list inside
the scene.
*/
void Scene3D_add_triangle(Scene3D* scene, Triangle3D triangle){
	long count = scene -> count;
	if(count == 0){
		scene->root->triangle = triangle;
		scene->root->next = NULL;
		scene->count += 1;
	}
	else{
		Triangle3DNode* ptr = malloc(sizeof(Triangle3DNode));
                ptr -> triangle = triangle;
                ptr -> next = NULL;
		Triangle3DNode* curr = scene->root;
		for(int i = 0; i < count; i++){
			if(curr -> next == NULL){
				curr -> next = ptr;
				scene -> count += 1; 
				i = count;
				return;
			}
			else{
				curr = curr -> next;
			}
		}
	}
}

void Scene3D_add_quadrilateral(Scene3D* scene, Coordinate3D a, Coordinate3D b, Coordinate3D c, Coordinate3D d){
	Triangle3D triangle_1 = (Triangle3D) {a, b, c};
	Triangle3D triangle_2 = (Triangle3D) {b, c, d};
	Triangle3D triangle_3 = (Triangle3D) {c, a, d};
	Triangle3D triangle_4 = (Triangle3D) {d, b, a};

	Scene3D_add_triangle(scene, triangle_1);
	Scene3D_add_triangle(scene, triangle_2);
	Scene3D_add_triangle(scene, triangle_3);
	Scene3D_add_triangle(scene, triangle_4);
}

void Scene3D_add_pyramid(Scene3D* scene, Coordinate3D origin, double width, double height, char* orientation){	
         if(strcmp(orientation, "forward") == 0 || strcmp(orientation, "backward") == 0){
                 Coordinate3D a,b,c,d;
                 a.x = origin.x - (width / 2);
                 a.y = origin.y;
                 a.z = origin.z + (width / 2);
                 b.x = origin.x + (width / 2);
                 b.y = origin.y;
                 b.z = origin.z + (width / 2);
                 c.x = origin.x - (width / 2);
                 c.y = origin.y;
                 c.z = origin.z - (width / 2);
                 d.x = origin.x + (width / 2);
                 d.y = origin.y;
                 d.z = origin.z - (width / 2);
		 Scene3D_add_quadrilateral(scene, a, b, c, d);
		if(strcmp(orientation, "forward") == 0){
			 Coordinate3D top;
                         top.x = origin.x;
                         top.y = origin.y + height;
                         top.z = origin.z;
                         Triangle3D triangle_1 = (Triangle3D) {a, b, top};
			 Triangle3D triangle_2 = (Triangle3D) {b, d, top};
                         Triangle3D triangle_3 = (Triangle3D) {a, c, top};
                         Triangle3D triangle_4 = (Triangle3D) {d, c, top};
	          	 Scene3D_add_triangle(scene, triangle_1);
                         Scene3D_add_triangle(scene, triangle_2);
                         Scene3D_add_triangle(scene, triangle_3);
                         Scene3D_add_triangle(scene, triangle_4);
		}
		else if(strcmp(orientation, "backward") == 0){
			  Coordinate3D top;
                          top.x = origin.x;
                          top.y = origin.y - height;
                          top.z = origin.z;
                          Triangle3D triangle_1 = (Triangle3D) {a, b, top};
                          Triangle3D triangle_2 = (Triangle3D) {b, d, top};
                          Triangle3D triangle_3 = (Triangle3D) {a, c, top};
                          Triangle3D triangle_4 = (Triangle3D) {d, c, top};
                          Scene3D_add_triangle(scene, triangle_1);
                          Scene3D_add_triangle(scene, triangle_2);
                          Scene3D_add_triangle(scene, triangle_3);
                          Scene3D_add_triangle(scene, triangle_4);
		}
	}
	else if(strcmp(orientation, "up") == 0 || strcmp(orientation, "down") == 0){
		  Coordinate3D a,b,c,d;
                  a.x = origin.x - (width / 2);
                  a.y = origin.y + (width / 2);;
                  a.z = origin.z;
                  b.x = origin.x + (width / 2);
                  b.y = origin.y + (width / 2);;
                  b.z = origin.z;
                  c.x = origin.x - (width / 2);
                  c.y = origin.y - (width / 2);;
                  c.z = origin.z;
                  d.x = origin.x + (width / 2);
                  d.y = origin.y - (width / 2);;
                  d.z = origin.z;
		  Scene3D_add_quadrilateral(scene, a, b, c, d);
                  if(strcmp(orientation, "up") == 0){
                          Coordinate3D top;
                          top.x = origin.x;
                          top.y = origin.y;
                          top.z = origin.z + height;
                          Triangle3D triangle_1 = (Triangle3D) {a, b, top};
                          Triangle3D triangle_2 = (Triangle3D) {b, d, top};
                          Triangle3D triangle_3 = (Triangle3D) {a, c, top};
                          Triangle3D triangle_4 = (Triangle3D) {d, c, top};
                          Scene3D_add_triangle(scene, triangle_1);
                          Scene3D_add_triangle(scene, triangle_2);
                          Scene3D_add_triangle(scene, triangle_3);
                          Scene3D_add_triangle(scene, triangle_4);
		}
		else if(strcmp(orientation, "down") == 0){
                          Coordinate3D top;
                          top.x = origin.x;
                          top.y = origin.y;
                          top.z = origin.z - height;
                          Triangle3D triangle_1 = (Triangle3D) {a, b, top};
                          Triangle3D triangle_2 = (Triangle3D) {b, d, top};
                          Triangle3D triangle_3 = (Triangle3D) {a, c, top};
                          Triangle3D triangle_4 = (Triangle3D) {d, c, top};
                          Scene3D_add_triangle(scene, triangle_1);
                          Scene3D_add_triangle(scene, triangle_2);
                          Scene3D_add_triangle(scene, triangle_3);
                          Scene3D_add_triangle(scene, triangle_4);
		}
	}
	else if(strcmp(orientation, "left") == 0 || strcmp(orientation, "right") == 0){
		   Coordinate3D a,b,c,d;
                   a.x = origin.x;
                   a.y = origin.y - (width / 2);
                   a.z = origin.z + (width / 2);
                   b.x = origin.x;
                   b.y = origin.y + (width / 2);
                   b.z = origin.z + (width / 2);
                   c.x = origin.x;
                   c.y = origin.y - (width / 2);
                   c.z = origin.z - (width / 2);
                   d.x = origin.x;
                   d.y = origin.y + (width / 2);
                   d.z = origin.z - (width / 2);
                   Scene3D_add_quadrilateral(scene, a, b, c, d);
                   if(strcmp(orientation, "left") == 0){
                           Coordinate3D top;
                           top.x = origin.x - height;
                           top.y = origin.y;
                           top.z = origin.z;
                           Triangle3D triangle_1 = (Triangle3D) {a, b, top};
                           Triangle3D triangle_2 = (Triangle3D) {b, d, top};
                           Triangle3D triangle_3 = (Triangle3D) {a, c, top};
                           Triangle3D triangle_4 = (Triangle3D) {d, c, top};
                           Scene3D_add_triangle(scene, triangle_1);
                           Scene3D_add_triangle(scene, triangle_2);
                           Scene3D_add_triangle(scene, triangle_3);
                           Scene3D_add_triangle(scene, triangle_4);
                 }
                 else if(strcmp(orientation, "right") == 0){
                           Coordinate3D top;
                           top.x = origin.x + height;
                           top.y = origin.y;
                           top.z = origin.z;
                           Triangle3D triangle_1 = (Triangle3D) {a, b, top};
                           Triangle3D triangle_2 = (Triangle3D) {b, d, top};
			   Triangle3D triangle_3 = (Triangle3D) {a, c, top};
                           Triangle3D triangle_4 = (Triangle3D) {d, c, top};
                           Scene3D_add_triangle(scene, triangle_1);
                           Scene3D_add_triangle(scene, triangle_2);
                           Scene3D_add_triangle(scene, triangle_3);
			   Scene3D_add_triangle(scene, triangle_4);
		}
	}
}

void Scene3D_add_cuboid(Scene3D* scene, Coordinate3D origin, double width, double height, double depth){
	Coordinate3D a; a.x = origin.x - width/2; a.y = origin.y + height/2; a.z = origin.z - depth/2;
	Coordinate3D b; b.x = origin.x + width/2; b.y = origin.y + height/2; b.z = origin.z - depth/2;
	Coordinate3D c; c.x = origin.x - width/2; c.y = origin.y - height/2; c.z = origin.z - depth/2;
	Coordinate3D d; d.x = origin.x + width/2; d.y = origin.y - height/2; d.z = origin.z - depth/2;
	Scene3D_add_quadrilateral(scene, a, b, c, d);
	Coordinate3D w; w.x = origin.x + width/2; w.y = origin.y + height/2; w.z = origin.z + depth/2;
	Coordinate3D x; x.x = origin.x + width/2; x.y = origin.y - height/2; x.z = origin.z + depth/2;
	Scene3D_add_quadrilateral(scene, b, d, w, x);
	Coordinate3D y; y.x = origin.x - width/2; y.y = origin.y + height/2; y.z = origin.z + depth/2;
	Coordinate3D z; z.x = origin.x - width/2; z.y = origin.y - height/2; z.z = origin.z + depth/2;
	Scene3D_add_quadrilateral(scene, y, z, w, x);
	Scene3D_add_quadrilateral(scene, y, z, a, c);
	Scene3D_add_quadrilateral(scene, a, b, w, y);
	Scene3D_add_quadrilateral(scene, c, d, z, x);
}
