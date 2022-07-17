#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* sub class: shape with some operation */
/* 抽像一个基础子类有三种基本操作：画图，移动图，销毁图 */
typedef struct shape_func_ops_s {
    int (*draw)(struct shape_func_ops_s *);
    int (*move)(struct shape_func_ops_s *, int newx, int newy);
    int (*destory)(struct shape_func_ops_s *);
} shape_func_ops_t;

/***************************************
 *   y+height
 *    | 
 *    |
 *    |
 *  (x,y) ------ x+width
 * 
**************************************/
/* rectangle class with shape sub class */
/* 方形继承形状这一子类 */
typedef struct rectangle_s {
    shape_func_ops_t ops;
    /* 私有成员 */
    int x;
    int y;
    int width;
    int height;
    int (*change_width_height)(shape_func_ops_t *ops, int new_width, int new_height);
} rectangle_t;

/***************************************
 *   
 *    
 *  
 *            (x,y) ----x+radius
 *               \
 *                \
 *                 (radius)
**************************************/
/* circle class with shape subclass */
/* 圆形继承形状这一子类 */
typedef struct circle_s {
    shape_func_ops_t ops;
    int x;
    int y;
    int radius;
    int (*change_radius)(shape_func_ops_t *ops, int radius);
} circle_t;

/* 形状这一类的公共类多态：打印方形 */
int rectangle_draw(shape_func_ops_t *ops)
{
    if (ops == NULL) {
        return -1;
    }

    rectangle_t *tmp = (rectangle_t *)ops;
    printf("rectangle draw: (x, y) = (%d, %d), width = %d, height = %d\n", tmp->x, tmp->y, tmp->width, tmp->height);
    return 0;
}

/* 形状这一类的公共类多态：打印圆形 */
int circle_draw(shape_func_ops_t *ops)
{
    if (ops == NULL) {
        return -1;
    }

    circle_t *tmp = (circle_t *)ops;
    printf("circle draw: (x, y) = (%d, %d), radius = %d\n", tmp->x, tmp->y, tmp->radius);
    return 0;
}

/* 方形的对外的public成员 */
int change_width_height(shape_func_ops_t *ops, int new_width, int new_height)
{
    if (ops == NULL) {
        return -1;
    }

    rectangle_t *tmp = (rectangle_t *)ops;
    printf("change the width:height from [%d %d] ", tmp->width, tmp->height);
    tmp->height = new_height;
    tmp->width = new_width;
    printf("to [%d %d] \n", tmp->width, tmp->height);
    return 0;
}

/* 圆形的对外的public成员 */
int change_radius(shape_func_ops_t *ops, int new_radius)
{
    if (ops == NULL) {
        return -1;
    }

    circle_t *tmp = (circle_t *)ops;
    printf("change the radius from %d ", tmp->radius);
    tmp->radius = new_radius;
    printf("to %d \n", tmp->radius);
    return 0;
}

/* 新生成一个方形 */
shape_func_ops_t *rectangle_new(int startx, int starty, int width_init, int height_init)
{
    if (width_init <= 0 || height_init <= 0) {
        return NULL;
    }

    rectangle_t *tmp = (rectangle_t *)malloc(sizeof(rectangle_t));
    tmp->height = height_init;
    tmp->width = width_init;
    tmp->x = startx;
    tmp->y = starty;
    tmp->ops.draw = rectangle_draw;
    tmp->ops.destory = NULL;
    tmp->ops.move = NULL;
    tmp->change_width_height = change_width_height;
    return (shape_func_ops_t *)tmp;
}

/* 新生成一个圆形 */
shape_func_ops_t *circle_new(int startx, int starty, int radius)
{
    if (radius <= 0) {
        return NULL;
    }

    circle_t *tmp = (circle_t *)malloc(sizeof(circle_t));
    tmp->radius = radius;
    tmp->x = startx;
    tmp->y = starty;
    tmp->ops.draw = circle_draw;
    tmp->ops.destory = NULL;
    tmp->ops.move = NULL;
    tmp->change_radius = change_radius;
    return (shape_func_ops_t *)tmp;
}

/* 多态归一化处理 */
int shape_draw(shape_func_ops_t *ops)
{
    if (ops == NULL) {
        return -1;
    }
    ops->draw(ops);
    return 0;
}

int main(int argc, char *argv[])
{
    printf("this is a oop with c demo \n");
    shape_func_ops_t *rectangle_obj = NULL;
    shape_func_ops_t *circle_obj = NULL;

    rectangle_obj = rectangle_new(0, 0, 10, 20);
    circle_obj = circle_new(0, 0, 30);

    /* 使用多态，不必关注具体是哪种对象 */
    if (shape_draw(rectangle_obj) == 0) {
        printf("print a rectanle shape pass \n");
    } else {
        printf("print a rectanle shape fail \n");
        assert(0);
    }

    if (shape_draw(circle_obj) == 0) {
        printf("print a rectanle shape pass \n");
    } else {
        printf("print a rectanle shape fail \n");
        assert(0);
    }    

    /* 同时方形和圆形的x,y,width,height,radius都是private, 只有shape做为public */
    /* 每个形状有自己的public */

    if (change_radius(circle_obj, 40) != 0) {
        assert(0);
    }
    if (change_width_height(rectangle_obj, 50, 60) != 0) {
        assert(0);
    }
    return 0;
}