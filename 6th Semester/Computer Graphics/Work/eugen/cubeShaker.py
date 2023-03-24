#!/usr/bin/python3
# cython: language_level=3
#This program is (c) Eugen Croitoru, "Al. I. Cuza" University of Iasi, Romania, 2020
#Licensed under GPLv3+
help = '''
if you don't have a C compiler:
pip install PyOpenGL pygame
if you do have a C compiler, accessible system-wide:
pip install PyOpenGL PyOpenGL_accelerate pygame

pyOpenGl reference at:
http://pyopengl.sourceforge.net/documentation/manual-3.0/index.html

pygame reference at e.g.:
https://www.pygame.org/docs/ref/event.html
 
This program works with cython.
How-to: create script named:
setup.py
------------------------------------------
#!/usr/bin/env python3
from setuptools import setup
from Cython.Build import cythonize

setup(
    name='Solver GL',
    ext_modules=cythonize("solverGl.pyx"),
    zip_safe=False,
)
------------------------------------------
run the cython-built module:
$ cp solverGl.py solverGl.pyx -f; python3 setup.py build_ext --inplace; python3 -c 'import solverGl; solverGl.main()'
'''
print(help)

import sys
import random, time
import math
from math import sin, cos
from ctypes import *
from contextlib import suppress #Amazing! That's why you're the best, Boss, the one and only!

from OpenGL.GL import *
#from OpenGL.GLU import *
#from OpenGL.GLUT import *

import pygame
from pygame.locals import *

#needs a compiler to install, provided by PyOpenGL_accelerate
#from OpengGL.GLU import *


# glConst = [0, GL_VERTEX_ARRAY, 0, 0, 0, GL_COLOR_ARRAY]
# glFunc  = [0, glVertexPointer, 0, 0, 0, glColorPointer]

# #init
# d[AS.vbo] = glGenBuffers(1)
# glBindBuffer(GL_ARRAY_BUFFER, d[AS.vbo])
# glBufferData(GL_ARRAY_BUFFER, len(d[AS.arr]) * 4, (c_float * len(d[AS.arr]))(*d[AS.arr]), GL_DYNAMIC_DRAW)
# err = glGetError()
# if err != 0:
#     print('Error during buffer allocation', err)
#     sys.exit(1)

# #update
# glBindBuffer(GL_ARRAY_BUFFER, d[AS.vbo])
# glBufferSubData(GL_ARRAY_BUFFER, 0, len(d[AS.arr]) * 4, (c_float * len(d[AS.arr]))(*d[AS.arr]))


# #draw
# glEnableClientState(d[AS.const])
# glBindBuffer(GL_ARRAY_BUFFER, d[AS.vbo])
# d[AS.func](d[AS.valNbr], GL_FLOAT, 0, None)
# glDrawArrays(styleDict[self.style][0], 0, self.length)
# glBindBuffer(GL_ARRAY_BUFFER, 0)

# glDisableClientState(d[AS.const])

def adjacentFaces(point = [0, 0, 0]):
    quad = []
    s = point
    for ii in range(3):
        pl = []
        p = s[:]
        q = s[:]
        for jj in range(3):
            if ii != jj:
                p[jj] = 1 - p[jj]
                q[jj] = p[jj]
                pl.append(p[:])
                p[jj] = 1 - p[jj]
        quad.append(s)
        quad.append(pl[0])
        quad.append(q)
        quad.append(pl[1])
    return(quad)
    
def genCube():
    cube = []
    f = adjacentFaces([0, 0, 0])
    f += adjacentFaces([1, 1, 1])
    for p in f:
        cube.append(p)
    return(cube)

def resizeCube(cube, l = 1, offset = [0, 0, 0]):
    cubeVector = []
    for p in cube:
        for ii in range(3):
            c = offset[ii] + p[ii] * l
            cubeVector.append(c)
    return(cubeVector)
    
def genCol(pointVector, opacity = 1):
    colVector = []
    for p in pointVector:
        c = p[:]
        c.append(opacity)
        colVector.extend(c)
    return(colVector)

class OglSimpleRenderer():
    def __init__(self, w = 1024, h = 1024, displayFlags = pygame.RESIZABLE | pygame.OPENGL | pygame.DOUBLEBUF, rotation = [-60, 0, 20], scale = 0.5, sceneVolume = [-1, 1, -1, 1, -1, 1]):
        self.w = w
        self.h = h
        self.displayFlags = displayFlags
        self.rotation = rotation
        self.scale = scale
        self.sceneVolume = sceneVolume
        self.viewVolume = self.sceneVolume[:]
        self.viewVolume[-2] *= 2
        self.viewVolume[-1] *= 2
        pygame.init()
        #init the display size and properties; we specifically request an OpenGL context and a resizable window
        pygame.display.set_mode( (w, h), displayFlags ) # pygame.DOUBLEBUF, pygame.NOFRAME ...
        screen = pygame.display.get_surface()
        if screen.get_flags() & DOUBLEBUF:
            print('Doublebuffered', end = ' ')
        else:
            print('Singlebuffered', end = ' ')
        if screen.get_flags() & OPENGL:
            print('OpenGl')
        else:
            print('No OpenGl')
        #set the window name
        pygame.display.set_caption('OpenGl Cube Shaker')
        #set the color used to erase the display
        glClearColor(0.0, 0.0, 0.0, 1.0)
        #set the width of lines being drawn
        glLineWidth(3)
        glPointSize(4)
        glEnable(GL_DEPTH_TEST)
        #glEnable(GL_MULTISAMPLE)
        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
        #glEnable(GL_POINT_SMOOTH)
        #glEnable(GL_LINE_SMOOTH)
        #glEnable(GL_POLYGON_SMOOTH)
        #glHint(GL_POINT_SMOOTH, GL_NICEST)
        self.objects = []

    def setProjection(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        glOrtho(*self.viewVolume)

    def setModelView(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        glRotatef(self.rotation[0], 1, 0, 0)
        glRotatef(self.rotation[1], 0, 1, 0)
        glRotatef(self.rotation[2], 0, 0, 1)
        glScalef(self.scale, self.scale, self.scale)

    def mouseDown(self, pos, button):
        if button == 4:
            self.scale *= 1.1
        if button == 5:
            self.scale /= 1.1
        
    def mouseMove(self, pos, rel, buttons):
        if buttons[2]:
            xrel, yrel = rel
            xrot = xrel / self.w * 180
            yrot = yrel / self.h * 180
            self.rotation[2] += xrot
            self.rotation[0] += yrot

    def keyDown(self, key):
        if key == 'escape':
            sys.exit(0)
        
    def step(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                #self.exitProgram()
                sys.exit(0)
                pass
            elif event.type == pygame.KEYDOWN:
                key = pygame.key.name(event.key)
                self.keyDown(key)
            elif event.type == pygame.KEYUP:
                key = pygame.key.name(event.key)
                #self.keyUp(key)
                pass
            elif event.type == pygame.MOUSEBUTTONDOWN:
                self.mouseDown(event.pos, event.button)
            elif event.type == pygame.MOUSEBUTTONUP:
                #self.mouseUp(event.pos, event.button)
                pass
            elif event.type == pygame.MOUSEMOTION:
                self.mouseMove(event.pos, event.rel, event.buttons)
            elif event.type == pygame.VIDEORESIZE:
                self.resize(event.size)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        self.display()
        glFlush()
        pygame.display.flip()
        pygame.time.wait(0)

    def loop(self):
        while True:
            self.step()

    def resize(self, size):
        self.w, self.h = size
        print('Window resized to', size)
        glViewport( 0, 0, GLsizei(self.w), GLsizei(self.h) )
        pygame.display.set_mode( (self.w, self.h), self.displayFlags )

    def display(self):
        self.integrate(self.objects[-1], self.shake())
        self.setProjection()
        self.setModelView()
        glMatrixMode(GL_MODELVIEW)
        for o in self.objects:
            self.render(o)

    def integrate(self, obj, accel = [0, 0, 0], dt = 1, collisionElasticity = 0.5):
        _, _, _, _, _, pos, vel, c = obj
        for ii in range(3):
            vel[ii] += accel[ii] * dt
        for ii in range(3):
            p = pos[ii] + vel[ii] * dt
            if p < self.sceneVolume[ii * 2]:
                p = self.sceneVolume[ii * 2]
                vel[ii] *= -collisionElasticity
            if p > self.sceneVolume[ii * 2 + 1]:
                p = self.sceneVolume[ii * 2 + 1]
                vel[ii] *= -collisionElasticity
            pos[ii] = p
 
    def shake(self, magnitude = 0.01):
        accel = []
        for ii in range(3):
            accel.append( (2 * random.random() - 1) * magnitude )
        return(accel)
            
    def render(self, obj):
        vertVbo, colVbo, l, cc, primitive, pos, _, _ = obj
        glPushMatrix()
        glTranslate(*pos)
        glEnableClientState(GL_VERTEX_ARRAY)
        glBindBuffer(GL_ARRAY_BUFFER, vertVbo)
        glVertexPointer(3, GL_FLOAT, 0, None)

        glEnableClientState(GL_COLOR_ARRAY)
        glBindBuffer(GL_ARRAY_BUFFER, colVbo)
        glColorPointer(cc, GL_FLOAT, 0, None)

        glDrawArrays(primitive, 0, l)
    
        glBindBuffer(GL_ARRAY_BUFFER, 0)
        glDisableClientState(GL_VERTEX_ARRAY)
        glDisableClientState(GL_COLOR_ARRAY)
        glPopMatrix()

    def addObject(self, vert, col, pos = [0, 0, 0], primitive = GL_QUADS):
        l = len(vert) // 3
        if len(col) // 3 == l:
            cc = 3
        else:
            cc = 4
        vertVbo = glGenBuffers(1)
        glBindBuffer(GL_ARRAY_BUFFER, vertVbo)
        glBufferData(GL_ARRAY_BUFFER, len(vert) * 4, (c_float * len(vert))(*vert), GL_DYNAMIC_DRAW)
        err = glGetError()
        if err != 0:
            print('Error during buffer allocation', err)
            sys.exit(1)

        colVbo = glGenBuffers(1)
        glBindBuffer(GL_ARRAY_BUFFER, colVbo)
        glBufferData(GL_ARRAY_BUFFER, len(col) * 4, (c_float * len(col))(*col), GL_DYNAMIC_DRAW)
        err = glGetError()
        if err != 0:
            print('Error during buffer allocation', err)
            sys.exit(1)
        c = [0, 0, 0]
        for ii in range(l):
            c[0] += vert[3 * ii]
            c[1] += vert[3 * ii + 1]
            c[2] += vert[3 * ii + 2]
        c = [ c[0] / l, c[1] / l, c[2] / l ]
        self.objects.append( [ vertVbo, colVbo, l, cc, primitive, pos, [0, 0, 0], c ] )



genCube()
hl = 10
sceneVolume = [-hl, hl, -hl, hl, -hl, hl]
cubePoints = genCube()
cubeVert = resizeCube(cubePoints)
col = genCol(cubePoints, opacity = 1)
app = OglSimpleRenderer(sceneVolume = sceneVolume)
app.addObject(cubeVert, col)
app.loop()
