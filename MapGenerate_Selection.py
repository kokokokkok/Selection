#%%
rate = 8
upFloor = 2
wall = 20
# VertexBuffer name="draw"
VRD0 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-2*rate,0,1*rate)
VRD1 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3*rate,upFloor,1*rate)
VRD2 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-3*rate,upFloor,-5*rate)
VRD3 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-11*rate,upFloor,-5*rate)
VRD4 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-11*rate,upFloor,1*rate)
VRD5 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-3*rate,0,1.5*rate)
VRD6 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-5*rate,0,1.5*rate)
VRD7 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-5*rate,upFloor,1*rate)
VRD8 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-5*rate,upFloor,2*rate)
VRD9 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate,upFloor,2*rate)
VRD10 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate,upFloor,1*rate)

VRD11 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-9*rate,0,1.5*rate)
VRD12 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-9*rate,upFloor,1*rate)
VRD13 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-11*rate,0,1.5*rate)
VRD14 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-11*rate,upFloor,1*rate)
VRD15 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-13*rate,0,1*rate)
VRD16 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-13*rate,0,3*rate)
VRD17 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-15*rate,0,3*rate)
VRD18 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate,0,13*rate)
VRD19 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-15*rate,upFloor,13*rate)
VRD20 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-13*rate,0,10*rate)

VRD21 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-13*rate,upFloor,15*rate)
VRD22 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-12.5*rate,0,13*rate)
VRD23 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-12.5*rate,0,10*rate)
VRD24 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-0*rate,upFloor,15*rate)
VRD25 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate,upFloor,10*rate)
VRD26 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-2*rate,upFloor,10*rate)
VRD27 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate,5,3*rate)
VRD28 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-2*rate,0,3*rate)
VRD29 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3.5*rate,0,10*rate)
VRD30 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3.5*rate,0,7*rate)

VRD31 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-4*rate,upFloor,10*rate)
VRD32 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-4*rate,0,7*rate)
VRD33 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-10*rate,upFloor,10*rate)
VRD34 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-10*rate,0,7*rate)
VRD35 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10.5*rate,0,10*rate)
VRD36 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10.5*rate,0,8*rate)
VRD37 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-6*rate,0,7*rate)
VRD38 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate,0,7*rate)
VRD39 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-6*rate,0,6.5*rate)
VRD40 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate,0,6.5*rate)
VRD41 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10*rate,upFloor,8*rate)

# 同じx、ｚ座標で2階層必要な頂点
VRD42 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate,upFloor,10*rate)#VRD20
VRD43 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate,upFloor,10*rate)#25
VRD44 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-2*rate,upFloor,10*rate)#26

# 壁
VRD45 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-2*rate,wall,1*rate)
VRD46 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3*rate,wall,1*rate)
VRD47 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-0*rate,wall,15*rate)
VRD48 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate,wall,10*rate)
VRD49 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-2*rate,wall,10*rate)
VRD50 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate,wall,3*rate)
VRD51 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-2*rate,wall,3*rate)
VRD52 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-4*rate,wall,10*rate)
VRD53 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-11*rate,wall,1*rate)
VRD54 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-13*rate,wall,1*rate)
VRD55 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-13*rate,wall,3*rate)
VRD56 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-15*rate,wall,3*rate)
VRD57 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate,wall,13*rate)
VRD58 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-15*rate,wall,13*rate)
VRD59 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-13*rate,wall,10*rate)
VRD60 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-10*rate,wall,10*rate)


VRD61 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-0*rate,0,15*rate)
VRD62 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-11*rate,0,1*rate)
VRD63 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-10*rate,0,10*rate)
VRD64 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-2*rate,0,10*rate)
VRD65 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-4*rate,0,10*rate)


VRD66 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-13*rate,wall,15*rate)
VRD67 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-3*rate,wall,-5*rate)
VRD68 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-11*rate,wall,-5*rate)
VRD69 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate,upFloor,13*rate)


# IndexBuffer name = "id"  判定に使うのに頂点を取る順番が存在する！
IB0 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(0,20,26)
IB1 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(15,0,20)

IB2 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(43,21,24)
IB3 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(42,43,21)

IB4 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(25,28,26)
IB5 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(28,27,25)

IB6 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(16,19,17)
IB7 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(18,19,16)

IB8 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(32,33,31)
IB9 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(34,32,33)

IB10 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(2,4,1)
IB11 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(3,2,4)

IB12 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(1,13,5)
IB13 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(14,1,13)

IB14 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(7,9,8)
IB15 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(10,7,9)

IB16 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(12,11,13)
IB17 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(14,13,12)

IB18 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(30,31,29)
IB19 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(32,30,31)

IB20 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(39,38,37)
IB21 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(40,39,38)

IB22 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(41,35,33)
IB23 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(36,41,35)

IB24 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(28,27,0)

# 壁 ---------------------------------------------------------------
IB25 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(61,27,47)
IB26 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(27,50,47)

IB27 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(27,0,45)
IB28 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(45,27,50)

IB29 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(0,5,45)
IB30 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(45,5,46)

IB31 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(28,26,49)
IB32 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(49,28,51)

IB33 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(65,64,52)
IB34 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(49,52,64)

IB35 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(62,15,53)
IB36 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(53,15,54)

IB37 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(15,16,54)
IB38 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(54,16,55)

IB39 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(17,16,55)
IB40 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(55,16,56)

IB41 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(15,16,54)
IB42 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(54,16,55)

IB43 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(17,16,55)
IB44 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(17,56,55)

IB45 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(17,19,56)
IB46 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(58,56,19)

IB47 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(18,19,57)
IB48 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(19,57,58)

IB49 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(63,20,59)
IB50 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(59,60,63)

IB51 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(21,24,66)
IB52 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(24,47,66)

IB53 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(18,21,66)
IB54 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(18,57,66)

IB55 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(5,2,46)
IB56 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(2,46,67)

IB57 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(2,3,67)
IB58 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(3,67,68)

IB59 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(3,4,53)
IB60 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(3,53,68)

IB61 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(20,69,19)

with open("map.txt","w") as f:
    #頂点座標
    f.write('<VertexBuffer name="draw">\n')
    f.write(VRD0)
    f.write(VRD1)
    f.write(VRD2)
    f.write(VRD3)
    f.write(VRD4)
    f.write(VRD5)
    f.write(VRD6)
    f.write(VRD7)
    f.write(VRD8)
    f.write(VRD9)
    f.write(VRD10)

    f.write(VRD11)
    f.write(VRD12)
    f.write(VRD13)
    f.write(VRD14)
    f.write(VRD15)
    f.write(VRD16)
    f.write(VRD17)
    f.write(VRD18)
    f.write(VRD19)
    f.write(VRD20)

    f.write(VRD21)
    f.write(VRD22)
    f.write(VRD23)
    f.write(VRD24)
    f.write(VRD25)
    f.write(VRD26)
    f.write(VRD27)
    f.write(VRD28)
    f.write(VRD29)
    f.write(VRD30)

    f.write(VRD31)
    f.write(VRD32)
    f.write(VRD33)
    f.write(VRD34)
    f.write(VRD35)
    f.write(VRD36)
    f.write(VRD37)
    f.write(VRD38)
    f.write(VRD39)
    f.write(VRD40)
    f.write(VRD41)
    f.write(VRD42)
    f.write(VRD43)
    f.write(VRD44)
    
    f.write(VRD45)
    f.write(VRD46)
    f.write(VRD47)
    f.write(VRD48)
    f.write(VRD49)
    f.write(VRD50)
    f.write(VRD51)
    f.write(VRD52)
    f.write(VRD53)
    f.write(VRD54)
    f.write(VRD55)
    f.write(VRD56)
    f.write(VRD57)
    f.write(VRD58)
    f.write(VRD59)
    f.write(VRD60)
    f.write(VRD61)
    f.write(VRD62)
    f.write(VRD63)
    f.write(VRD64)
    f.write(VRD65)
    f.write(VRD66)
    f.write(VRD67)
    f.write(VRD68)
    f.write(VRD69)

    f.write('</VertexBuffer>\n')

    f.write('<VertexBuffer name="collision">\n')
    #頂点座標
    f.write(VRD0)
    f.write(VRD1)
    f.write(VRD2)
    f.write(VRD3)
    f.write(VRD4)
    f.write(VRD5)
    f.write(VRD6)
    f.write(VRD7)
    f.write(VRD8)
    f.write(VRD9)
    f.write(VRD10)
    f.write(VRD11)
    f.write(VRD12)
    f.write(VRD13)
    f.write(VRD14)
    f.write(VRD15)
    f.write(VRD16)
    f.write(VRD17)
    f.write(VRD18)
    f.write(VRD19)
    f.write(VRD20)
    f.write(VRD21)
    f.write(VRD22)
    f.write(VRD23)
    f.write(VRD24)
    f.write(VRD25)
    f.write(VRD26)
    f.write(VRD27)
    f.write(VRD28)
    f.write(VRD29)
    f.write(VRD30)
    f.write(VRD31)
    f.write(VRD32)
    f.write(VRD33)
    f.write(VRD34)
    f.write(VRD35)
    f.write(VRD36)
    f.write(VRD37)
    f.write(VRD38)
    f.write(VRD39)
    f.write(VRD40)
    f.write(VRD41)
    f.write(VRD42)
    f.write(VRD43)
    f.write(VRD44)
    f.write(VRD45)
    f.write(VRD46)
    f.write(VRD47)
    f.write(VRD48)
    f.write(VRD49)
    f.write(VRD50)
    f.write(VRD51)
    f.write(VRD52)
    f.write(VRD53)
    f.write(VRD54)
    f.write(VRD55)
    f.write(VRD56)
    f.write(VRD57)
    f.write(VRD58)
    f.write(VRD59)
    f.write(VRD60)
    f.write(VRD61)
    f.write(VRD62)
    f.write(VRD63)
    f.write(VRD64)
    f.write(VRD65)
    f.write(VRD66)
    f.write(VRD67)
    f.write(VRD68)
    f.write(VRD69)
      
    
    f.write('</VertexBuffer>\n')

    f.write('<IndexBuffer name="ib">\n')
    #頂点インデックス
    f.write(IB0)
    f.write(IB1)

    f.write(IB2)
    f.write(IB3)
    
    f.write(IB4)
    f.write(IB5)
    
    f.write(IB6)
    f.write(IB7)
    
    f.write(IB8)
    f.write(IB9)

    f.write(IB10)
    f.write(IB11)
    
    f.write(IB12)
    f.write(IB13)
    
    #f.write(IB14)
    #f.write(IB15)
    
    #f.write(IB16)
    #f.write(IB17)
    
    #f.write(IB18)
    #f.write(IB19)
    
    #f.write(IB20)
    #f.write(IB21)
    
    #f.write(IB22)
    #f.write(IB23)
    
    f.write(IB24)
    f.write(IB25)
    f.write(IB26)
    f.write(IB27)
    f.write(IB28)
    f.write(IB29)
    f.write(IB30)
    f.write(IB31)
    f.write(IB32)
    f.write(IB33)
    f.write(IB34)
    f.write(IB35)
    f.write(IB36)
    f.write(IB37)
    f.write(IB38)
    f.write(IB39)
    f.write(IB40)
    f.write(IB41)
    f.write(IB42)
    f.write(IB43)
    f.write(IB44)
    f.write(IB45)
    f.write(IB46)
    f.write(IB47)
    f.write(IB48)
    f.write(IB49)
    f.write(IB50)
    f.write(IB51)
    f.write(IB52)
    f.write(IB53)
    f.write(IB54)
    f.write(IB55)
    f.write(IB56)
    f.write(IB57)
    f.write(IB58)
    f.write(IB59)
    f.write(IB60)
    f.write(IB61)
    f.write('</IndexBuffer>\n')


    f.write('<Texture name="texture" filename="black.tga"/>\n<Batch\nname="draw"\nvertexBuffer="draw"\nindexBuffer="ib"\ntexture="texture"\nblend="opaque">\n</Batch>\n<Batch \nname="collision"\nvertexBuffer="collision"\nindexBuffer="ib"\n</Batch>')

# %%
#%%
rate = 2#5
upFloor = 2
# VertexBuffer name="draw"
VRD0 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-2*rate,0,1*rate)
VRD15 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-13*rate,0,1*rate)
VRD20 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-13*rate,0,10*rate)
VRD26 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-2*rate,0,10*rate)
# IndexBuffer name = "id"
IB0 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(0,2,3)
IB1 = '<Triangle indices="{0}, {1}, {2}"/>\n'.format(2,1,0)

with open("map.txt","w") as f:
    #頂点座標
    f.write('<VertexBuffer name="draw">\n')
    f.write(VRD0)
    f.write(VRD15)
    f.write(VRD20)
    f.write(VRD26)
    f.write('</VertexBuffer>\n')

    f.write('<VertexBuffer name="collision">\n')
    f.write(VRD0)
    f.write(VRD15)
    f.write(VRD20)
    f.write(VRD26)
    f.write('</VertexBuffer>\n')


    f.write('<IndexBuffer name="ib">\n')
    #頂点インデックス
    f.write(IB0)
    f.write(IB1)
   
    f.write('</IndexBuffer>\n')


    f.write('<Texture name="texture" filename="black.tga"/>\n<Batch\nname="draw"\nvertexBuffer="draw"\nindexBuffer="ib"\ntexture="texture"\nblend="opaque">\n</Batch>\n<Batch \nname="collision"\nvertexBuffer="collision"\nindexBuffer="ib"\n</Batch>')

# %%

# collision 
dex = 0.5
VRDC0 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-2*rate-dex,0,1*rate-dex)
VRDC1 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3*rate-dex,upFloor,1*rate-dex)
VRDC2 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3*rate-dex,upFloor,0*rate-dex)
VRDC3 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-11*rate-dex,upFloor,0*rate-dex)
VRDC4 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-11*rate-dex,upFloor,1*rate-dex)
VRDC5 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3*rate-dex,0,1.5*rate-dex)
VRDC6 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-5*rate-dex,0,1.5*rate-dex)
VRDC7 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-5*rate-dex,upFloor,1*rate-dex)
VRDC8 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-5*rate-dex,upFloor,2*rate-dex)
VRDC9 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate-dex,upFloor,2*rate-dex)
VRDC10 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate-dex,upFloor,1*rate-dex)

VRDC11 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-9*rate-dex,0,1.5*rate-dex)
VRDC12 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-9*rate-dex,upFloor,1*rate-dex)
VRDC13 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-11*rate-dex,0,1.5*rate-dex)
VRDC14 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-11*rate-dex,upFloor,1*rate-dex)
VRDC15 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-13*rate-dex,0,1*rate-dex)
VRDC16 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate-dex,0,3*rate-dex)
VRDC17 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-15*rate-dex,0,3*rate-dex)
VRDC18 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate-dex,0,13*rate-dex)
VRDC19 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-15*rate-dex,upFloor,13*rate-dex)
VRDC20 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-13*rate-dex,0,10*rate-dex)

VRDC21 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-13*rate-dex,upFloor,15*rate-dex)
VRDC22 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-12.5*rate-dex,0,13*rate-dex)
VRDC23 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-12.5*rate-dex,0,10*rate-dex)
VRDC24 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-0*rate-dex,upFloor,15*rate-dex)
VRDC25 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate-dex,0,10*rate-dex)
VRDC26 = '<Vertex position="{0}, {1}, {2}" uv="0, 1"/>\n'.format(-2*rate-dex,0,10*rate-dex)
VRDC27 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate-dex,0,3*rate-dex)
VRDC28 = '<Vertex position="{0}, {1}, {2}" uv="1, 1"/>\n'.format(-2*rate-dex,0,3*rate-dex)
VRDC29 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3.5*rate-dex,0,10*rate-dex)
VRDC30 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-3.5*rate-dex,0,7*rate-dex)

VRDC31 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-4*rate-dex,upFloor,10*rate-dex)
VRDC32 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-4*rate-dex,upFloor,7*rate-dex)
VRDC33 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10*rate-dex,upFloor,10*rate-dex)
VRDC34 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10*rate-dex,upFloor,7*rate-dex)
VRDC35 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10.5*rate-dex,0,10*rate-dex)
VRDC36 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10.5*rate-dex,0,8*rate-dex)
VRDC37 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-6*rate-dex,0,7*rate-dex)
VRDC38 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate-dex,0,7*rate-dex)
VRDC39 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-6*rate-dex,0,6.5*rate-dex)
VRDC40 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-7*rate-dex,0,6.5*rate-dex)
VRDC41 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-10*rate-dex,upFloor,8*rate-dex)

# 同じx、ｚ座標で2階層必要な頂点
VRDC42 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-13*rate-dex,upFloor,10*rate-dex)#VRDC20
VRDC43 = '<Vertex position="{0}, {1}, {2}" uv="1, 0"/>\n'.format(-0*rate-dex,upFloor,10*rate-dex)#25
VRDC44 = '<Vertex position="{0}, {1}, {2}" uv="0, 0"/>\n'.format(-2*rate-dex,upFloor,10*rate)#26




