#Mettre dans dossier UI

from guizero import App, Text,PushButton,Slider,TextBox
app=App(title="Symbot",layout="grid",width=800,height=700)
C_Title=Text(app,text="Coordinates",grid=[25,50])
red=(255,0,0)
green=(0,255,0)
cer=(86,87,255)
mint=(156,255,154)
Peri=(155,156,255)
app.bg=Peri
open_on="Boutonpinceouverteonp.png"
open_off="Boutonpinceouverteoffp.png"
closed_on="Boutonpincefermeeonp.png"
closed_off="Boutonpincefermeep.png"
is_op=False
ii=0


#grip_com=ButtonGroup(app,command=op_cl_grip,options)


def op_grip(op,button1,button2):
    if not op:
        #open_gripper()
        op=True
        button1.image=open_on
        button2.image=closed_off


def cl_grip(op,button1,button2):
    #close_gripper()
    button1.image=open_off
    button2.image=closed_on
    op=False


def ch_mode(button1,button2):
    button1.bg=mint
    button2.bg=Peri


def cart_mode():
    #This is where we go in cartesian mode
    a=1
    a=a+1


def joint_mode():
    b=2
    b=b+2


def change_val(coord,go_but,ch_but,can_but,u,d):
    ch_but.hide()
    coord.show()
    go_but.show()
    go_but.enable()
    can_but.show()
    can_but.enable()
    u.hide()
    u.disable()
    d.disable()
    d.hide()


def can_but_f(coord,go_but,ch_but,can_but,u,d):
    go_but.disable()
    go_but.hide()
    coord.clear()
    coord.hide()
    ch_but.show()
    u.enable()
    u.show()
    d.enable()
    d.show()
    can_but.hide()
    can_but.disable()


def go_but_f(coord,go_but,ch_but,can_but,u,d,text):
    try:
        new_val=float(coord.value)
        go_but.disable()
        go_but.hide()
        coord.bg=Peri
        coord.clear()
        coord.hide()
        ch_but.show()
        u.enable()
        u.show()
        d.enable()
        d.show()
        can_but.hide()
        can_but.disable()
        text.value=new_val
    except:
        coord.bg=red


cart_mode_but=PushButton(app,cart_mode,text="Cartesian Mode",grid=[20,0])
joint_mode_but=PushButton(app,joint_mode,text="Joint Mode",grid=[20,10])
op_grip_but=PushButton(app,image=open_on,grid=[100,0],width=108,height=97)
cl_grip_but=PushButton(app,image=closed_off,grid=[100,10],width=108,height=97)
op_grip_but.update_command(op_grip,args=(is_op,op_grip_but,cl_grip_but))
cl_grip_but.update_command(cl_grip,args=(is_op,op_grip_but,cl_grip_but))
cart_mode_but.update_command(ch_mode,args=(cart_mode_but,joint_mode_but))
joint_mode_but.update_command(ch_mode,args=(joint_mode_but,cart_mode_but))
X_lab=Text(app,text="X",grid=[0,60],align="left")
Y_lab=Text(app,text="Y",grid=[0,70],align="left")
Z_lab=Text(app,text="Z",grid=[0,80],align="left")
J1_lab=Text(app,text="J1",grid=[0,90],align="left")
J2_lab=Text(app,text="J2",grid=[0,100],align="left")
J3_lab=Text(app,text="J3",grid=[0,110],align="left")
X_val=Text(app,text="???",grid=[10,60],align="left")
Y_val=Text(app,text="???",grid=[10,70],align="left")
Z_val=Text(app,text="???",grid=[10,80],align="left")
J1_val=Text(app,text="???",grid=[10,90],align="left")
J2_val=Text(app,text="???",grid=[10,100],align="left")
J3_val=Text(app,text="???",grid=[10,110],align="left")
X_coord=TextBox(app,grid=[25,60],visible=False)
Y_coord=TextBox(app,grid=[25,70],visible=False)
Z_coord=TextBox(app,grid=[25,80],visible=False)
J1_coord=TextBox(app,grid=[25,90],visible=False)
J2_coord=TextBox(app,grid=[25,100],visible=False)
J3_coord=TextBox(app,grid=[25,110],visible=False)
X_U=PushButton(app,text="▲",grid=[25,59])
X_D=PushButton(app,text="▼",grid=[25,60])
Y_U=PushButton(app,text="▲",grid=[25,69])
Y_D=PushButton(app,text="▼",grid=[25,70])
Z_U=PushButton(app,text="▲",grid=[25,79])
Z_D=PushButton(app,text="▼",grid=[25,80])
J1_U=PushButton(app,text="▲",grid=[25,89])
J1_D=PushButton(app,text="▼",grid=[25,90])
J2_U=PushButton(app,text="▲",grid=[25,99])
J2_D=PushButton(app,text="▼",grid=[25,100])
J3_U=PushButton(app,text="▲",grid=[25,109])
J3_D=PushButton(app,text="▼",grid=[25,110])
X_U.text_size=4
X_D.text_size=4
Y_U.text_size=4
Y_D.text_size=4
Z_U.text_size=4
Z_D.text_size=4
J1_U.text_size=4
J1_D.text_size=4
J2_U.text_size=4
J2_D.text_size=4
J3_U.text_size=4
J3_D.text_size=4
X_ch=PushButton(app,text="Move",grid=[50,60])
X_Go=PushButton(app,text="Go",grid=[50,60],enabled=False,visible=False)
X_Ca=PushButton(app,text="Cancel",grid=[75,60],enabled=False,visible=False)
Y_ch=PushButton(app,text="Move",grid=[50,70])
Y_Go=PushButton(app,text="Go",grid=[50,70],enabled=False,visible=False)
Y_Ca=PushButton(app,text="Cancel",grid=[75,70],enabled=False,visible=False)
Z_ch=PushButton(app,text="Move",grid=[50,80])
Z_Go=PushButton(app,text="Go",grid=[50,80],enabled=False,visible=False)
Z_Ca=PushButton(app,text="Cancel",grid=[75,80],enabled=False,visible=False)
J1_ch=PushButton(app,text="Move",grid=[50,90])
J1_Go=PushButton(app,text="Go",grid=[50,90],enabled=False,visible=False)
J1_Ca=PushButton(app,text="Cancel",grid=[75,90],enabled=False,visible=False)
J2_ch=PushButton(app,text="Move",grid=[50,100])
J2_Go=PushButton(app,text="Go",grid=[50,100],enabled=False,visible=False)
J2_Ca=PushButton(app,text="Cancel",grid=[75,100],enabled=False,visible=False)
J3_ch=PushButton(app,text="Move",grid=[50,110])
J3_Go=PushButton(app,text="Go",grid=[50,110],enabled=False,visible=False)
J3_Ca=PushButton(app,text="Cancel",grid=[75,110],enabled=False,visible=False)
X_ch.update_command(change_val,args=(X_coord,X_Go,X_ch,X_Ca,X_U,X_D))
X_Go.update_command(go_but_f,args=(X_coord,X_Go,X_ch,X_Ca,X_U,X_D,X_val))
X_Ca.update_command(can_but_f,args=(X_coord,X_Go,X_ch,X_Ca,X_U,X_D))
Y_ch.update_command(change_val,args=(Y_coord,Y_Go,Y_ch,Y_Ca,Y_U,Y_D))
Y_Go.update_command(go_but_f,args=(Y_coord,Y_Go,Y_ch,Y_Ca,Y_U,Y_D,Y_val))
Y_Ca.update_command(can_but_f,args=(Y_coord,Y_Go,Y_ch,Y_Ca,Y_U,Y_D))
Z_ch.update_command(change_val,args=(Z_coord,Z_Go,Z_ch,Z_Ca,Z_U,Z_D))
Z_Go.update_command(go_but_f,args=(Z_coord,Z_Go,Z_ch,Z_Ca,Z_U,Z_D,Z_val))
Z_Ca.update_command(can_but_f,args=(Z_coord,Z_Go,Z_ch,Z_Ca,Z_U,Z_D))
J1_ch.update_command(change_val,args=(J1_coord,J1_Go,J1_ch,J1_Ca,J1_U,J1_D))
J1_Go.update_command(go_but_f,args=(J1_coord,J1_Go,J1_ch,J1_Ca,J1_U,J1_D,J1_val))
J1_Ca.update_command(can_but_f,args=(J1_coord,J1_Go,J1_ch,J1_Ca,J1_U,J1_D))
J2_ch.update_command(change_val,args=(J2_coord,J2_Go,J2_ch,J2_Ca,J2_U,J2_D))
J2_Go.update_command(go_but_f,args=(J2_coord,J2_Go,J2_ch,J2_Ca,J2_U,J2_D,J2_val))
J2_Ca.update_command(can_but_f,args=(J2_coord,J2_Go,J2_ch,J2_Ca,J2_U,J2_D))
J3_ch.update_command(change_val,args=(J3_coord,J3_Go,J3_ch,J3_Ca,J3_U,J3_D))
J3_Go.update_command(go_but_f,args=(J3_coord,J3_Go,J3_ch,J3_Ca,J3_U,J3_D,J3_val))
J3_Ca.update_command(can_but_f,args=(J3_coord,J3_Go,J3_ch,J3_Ca,J3_U,J3_D))
S_title=Text(app,text="Sensors",grid=[175,50])
p_lab=Text(app,text="Pinky",grid=[150,90],align="left")
i_lab=Text(app,text="Index",grid=[150,60],align="left")
m_lab=Text(app,text="Middle",grid=[150,70],align="left")
r_lab=Text(app,text="Ring",grid=[150,80],align="left")
o_lab=Text(app,text="IMU",grid=[150,100],align="left")
p_sl=Slider(app,grid=[175,90])
i_sl=Slider(app,grid=[175,60])
m_sl=Slider(app,grid=[175,70])
r_sl=Slider(app,grid=[175,80])
o_sl=Slider(app,grid=[175,100])
i_cl=PushButton(app,text="Set as closed",grid=[225,60])
m_cl=PushButton(app,text="Set as closed",grid=[225,70])
r_cl=PushButton(app,text="Set as closed",grid=[225,80])
p_cl=PushButton(app,text="Set as closed",grid=[225,90])
i_op=PushButton(app,text="Set as open",grid=[200,60])
m_op=PushButton(app,text="Set as open",grid=[200,70])
r_op=PushButton(app,text="Set as open",grid=[200,80])
p_op=PushButton(app,text="Set as open",grid=[200,90])
i_cl.bg=cer
m_cl.bg=cer
r_cl.bg=cer
p_cl.bg=cer
i_op.bg=mint
m_op.bg=mint
r_op.bg=mint
p_op.bg=mint


app.display()
