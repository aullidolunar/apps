<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <requires lib="gtk+" version="2.24"/>
  <!-- interface-naming-policy project-wide -->
  <object class="GtkListStore" id="liststore1">
    <columns>
      <!-- column-name GdkPixbuf1 -->
      <column type="GdkPixbuf"/>
      <!-- column-name gchararray1 -->
      <column type="gchararray"/>
    </columns>
  </object>
  <object class="GtkTreeModelSort" id="treemodelsort1">
    <property name="model">liststore1</property>
  </object>
  <object class="GtkWindow" id="window1">
    <property name="can_focus">False</property>
    <property name="window_position">center</property>
    <signal name="destroy" handler="on_window1_destroy" swapped="no"/>
    <signal name="delete-event" handler="on_window1_delete_event" swapped="no"/>
    <child>
      <object class="GtkVBox" id="vbox1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <child>
          <object class="GtkVBox" id="vbox2">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="border_width">10</property>
            <child>
              <object class="GtkFrame" id="frame1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <child>
                  <object class="GtkAlignment" id="alignment1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="top_padding">10</property>
                    <property name="bottom_padding">10</property>
                    <property name="left_padding">10</property>
                    <property name="right_padding">10</property>
                    <child>
                      <object class="GtkLabel" id="label2">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="xalign">0</property>
                        <property name="label">...</property>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel" id="label1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">&lt;b&gt;Current theme&lt;/b&gt;</property>
                    <property name="use_markup">True</property>
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
              <object class="GtkVBox" id="vbox3">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <child>
                  <placeholder/>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="padding">10</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkScrolledWindow" id="scrolledwindow1">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="hscrollbar_policy">automatic</property>
                <property name="vscrollbar_policy">automatic</property>
                <property name="shadow_type">etched-in</property>
                <child>
                  <object class="GtkTreeView" id="treeview1">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="model">treemodelsort1</property>
                    <signal name="key-press-event" handler="on_treeview1_key_press_event" swapped="no"/>
                    <signal name="row-activated" handler="on_treeview1_row_activated" swapped="no"/>
                    <child>
                      <object class="GtkTreeViewColumn" id="treeviewcolumn1">
                        <property name="title" translatable="yes">Theme list</property>
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
                    </child>
                  </object>
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
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkHSeparator" id="hseparator1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkHBox" id="hbox1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkButton" id="button1">
                <property name="label">gtk-execute</property>
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="tooltip_text" translatable="yes">Launch SLim with current selected theme</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="on_button1_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="button2">
                <property name="label">gtk-copy</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="on_button2_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">False</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="button3">
                <property name="label">gtk-quit</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="on_button3_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">2</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">False</property>
            <property name="position">2</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
