<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.18.3 -->
<interface>
  <requires lib="gtk+" version="3.10"/>
  <object class="GtkListStore" id="liststore1">
    <columns>
      <!-- column-name GdkPixbuf1 -->
      <column type="GdkPixbuf"/>
      <!-- column-name gchararray1 -->
      <column type="gchararray"/>
      <!-- column-name gchararray2 -->
      <column type="gchararray"/>
    </columns>
  </object>
  <object class="GtkListStore" id="liststore2">
    <columns>
      <!-- column-name GdkPixbuf1 -->
      <column type="GdkPixbuf"/>
      <!-- column-name gchararray1 -->
      <column type="gchararray"/>
      <!-- column-name gchararray2 -->
      <column type="gchararray"/>
    </columns>
  </object>
  <object class="GtkListStore" id="liststore3">
    <columns>
      <!-- column-name GdkPixbuf1 -->
      <column type="GdkPixbuf"/>
      <!-- column-name gchararray1 -->
      <column type="gchararray"/>
      <!-- column-name gint1 -->
      <column type="gint"/>
    </columns>
  </object>
  <object class="GtkWindow" id="window1">
    <property name="can_focus">False</property>
    <property name="window_position">center</property>
    <signal name="delete-event" handler="on_window1_delete_event" swapped="no"/>
    <signal name="destroy" handler="on_window1_destroy" swapped="no"/>
    <child>
      <object class="GtkBox" id="box1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkToolbar" id="toolbar1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkToolButton" id="toolbutton1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="tooltip_text" translatable="yes">Starts the convertion</property>
                <property name="use_underline">True</property>
                <signal name="clicked" handler="on_toolbutton1_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="homogeneous">True</property>
              </packing>
            </child>
            <child>
              <object class="GtkSeparatorToolItem" id="separatortoolitem1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="homogeneous">False</property>
              </packing>
            </child>
            <child>
              <object class="GtkToolButton" id="toolbutton2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="tooltip_text" translatable="yes">About the program</property>
                <property name="use_underline">True</property>
                <signal name="clicked" handler="on_toolbutton2_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="homogeneous">True</property>
              </packing>
            </child>
            <child>
              <object class="GtkToolButton" id="toolbutton3">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="tooltip_text" translatable="yes">Quits the application</property>
                <property name="use_underline">True</property>
                <signal name="clicked" handler="on_toolbutton3_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="homogeneous">True</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox" id="box2">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_left">10</property>
            <property name="margin_right">10</property>
            <property name="margin_top">10</property>
            <property name="margin_bottom">10</property>
            <property name="orientation">vertical</property>
            <child>
              <object class="GtkFrame" id="frame1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">etched-out</property>
                <child>
                  <object class="GtkAlignment" id="alignment1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="top_padding">10</property>
                    <property name="bottom_padding">10</property>
                    <property name="left_padding">10</property>
                    <property name="right_padding">10</property>
                    <child>
                      <object class="GtkBox" id="box6">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkBox" id="box7">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <child>
                              <object class="GtkLabel" id="label4">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="xalign">0</property>
                                <property name="label" translatable="yes" comments="Leave a spacer after :">Set input directory: </property>
                              </object>
                              <packing>
                                <property name="expand">False</property>
                                <property name="fill">False</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkComboBox" id="combobox1">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="model">liststore1</property>
                                <property name="active">0</property>
                                <signal name="changed" handler="on_combobox1_changed" swapped="no"/>
                                <child>
                                  <object class="GtkCellRendererPixbuf" id="cellrendererpixbuf1"/>
                                  <attributes>
                                    <attribute name="pixbuf">0</attribute>
                                  </attributes>
                                </child>
                                <child>
                                  <object class="GtkCellRendererText" id="cellrenderertext1"/>
                                  <attributes>
                                    <attribute name="text">1</attribute>
                                  </attributes>
                                </child>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">2</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">False</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkCheckButton" id="checkbutton1">
                            <property name="label" translatable="yes">Delete source file</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">False</property>
                            <property name="xalign">0</property>
                            <property name="active">True</property>
                            <property name="draw_indicator">True</property>
                            <signal name="toggled" handler="on_checkbutton1_toggled" swapped="no"/>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel" id="label2">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Input configuration</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkBox" id="box3">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="orientation">vertical</property>
                <child>
                  <placeholder/>
                </child>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frame2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">out</property>
                <child>
                  <object class="GtkAlignment" id="alignment2">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="top_padding">10</property>
                    <property name="bottom_padding">10</property>
                    <property name="left_padding">10</property>
                    <property name="right_padding">10</property>
                    <child>
                      <object class="GtkBox" id="box8">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkBox" id="box9">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <child>
                              <object class="GtkLabel" id="label5">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="xalign">0</property>
                                <property name="label" translatable="yes" comments="Leave a space after :">Set output directory: </property>
                              </object>
                              <packing>
                                <property name="expand">False</property>
                                <property name="fill">False</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkComboBox" id="combobox2">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="model">liststore2</property>
                                <signal name="changed" handler="on_combobox2_changed" swapped="no"/>
                                <child>
                                  <object class="GtkCellRendererPixbuf" id="cellrendererpixbuf2"/>
                                  <attributes>
                                    <attribute name="pixbuf">0</attribute>
                                  </attributes>
                                </child>
                                <child>
                                  <object class="GtkCellRendererText" id="cellrenderertext2"/>
                                  <attributes>
                                    <attribute name="text">1</attribute>
                                  </attributes>
                                </child>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">2</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">False</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkBox" id="box10">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <child>
                              <object class="GtkLabel" id="label6">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="xalign">0</property>
                                <property name="label" translatable="yes" comments="Leave a space after :">Set bitrate level: </property>
                              </object>
                              <packing>
                                <property name="expand">False</property>
                                <property name="fill">False</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkComboBox" id="combobox3">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="model">liststore3</property>
                                <signal name="changed" handler="on_combobox3_changed" swapped="no"/>
                                <child>
                                  <object class="GtkCellRendererPixbuf" id="cellrendererpixbuf3"/>
                                  <attributes>
                                    <attribute name="pixbuf">0</attribute>
                                  </attributes>
                                </child>
                                <child>
                                  <object class="GtkCellRendererText" id="cellrenderertext3"/>
                                  <attributes>
                                    <attribute name="text">1</attribute>
                                  </attributes>
                                </child>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">2</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">False</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel" id="label3">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Output configuration</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkBox" id="box4">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="orientation">vertical</property>
                <child>
                  <placeholder/>
                </child>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">3</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">True</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkSeparator" id="separator1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">2</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox" id="box5">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkImage" id="image1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="stock">gtk-missing-image</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="xalign">0</property>
                <property name="label" translatable="yes">Ready</property>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">3</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
