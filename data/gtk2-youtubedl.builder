<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <requires lib="gtk+" version="2.24"/>
  <!-- interface-naming-policy project-wide -->
  <object class="GtkListStore" id="liststore1">
    <columns>
      <!-- column-name icon -->
      <column type="GdkPixbuf"/>
      <!-- column-name url -->
      <column type="gchararray"/>
      <!-- column-name outdir -->
      <column type="gchararray"/>
      <!-- column-name optype -->
      <column type="gchararray"/>
      <!-- column-name opcmd -->
      <column type="gint"/>
      <!-- column-name retval -->
      <column type="gboolean"/>
    </columns>
    <signal name="row-deleted" handler="on_liststore1_row_deleted" swapped="no"/>
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
              <object class="GtkLabel" id="label1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="xalign">0</property>
                <property name="label" translatable="yes">Input video URL:</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkHBox" id="hbox1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <child>
                  <object class="GtkEntry" id="entry1">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="invisible_char">•</property>
                    <property name="primary_icon_activatable">False</property>
                    <property name="secondary_icon_activatable">False</property>
                    <property name="primary_icon_sensitive">True</property>
                    <property name="secondary_icon_sensitive">True</property>
                    <signal name="changed" handler="on_entry1_changed" swapped="no"/>
                  </object>
                  <packing>
                    <property name="expand">True</property>
                    <property name="fill">True</property>
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkButton" id="button1">
                    <property name="label">gtk-add</property>
                    <property name="visible">True</property>
                    <property name="sensitive">False</property>
                    <property name="can_focus">True</property>
                    <property name="receives_default">True</property>
                    <property name="use_stock">True</property>
                    <signal name="clicked" handler="on_button1_clicked" swapped="no"/>
                  </object>
                  <packing>
                    <property name="expand">False</property>
                    <property name="fill">False</property>
                    <property name="position">1</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkHBox" id="hbox2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <child>
                  <object class="GtkLabel" id="label3">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Operation type</property>
                  </object>
                  <packing>
                    <property name="expand">False</property>
                    <property name="fill">False</property>
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkComboBoxText" id="comboboxtext1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="active">1</property>
                    <items>
                      <item>MP3</item>
                      <item translatable="yes">MP3 (best)</item>
                      <item>Video</item>
                      <item>3GP</item>
                      <item>Facebook</item>
                    </items>
                    <signal name="changed" handler="on_comboboxtext1_changed" swapped="no"/>
                  </object>
                  <packing>
                    <property name="expand">False</property>
                    <property name="fill">False</property>
                    <property name="position">1</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkCheckButton" id="checkbutton1">
                <property name="label" translatable="yes">Enable user credentials</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">False</property>
                <property name="draw_indicator">True</property>
                <signal name="toggled" handler="on_checkbutton1_toggled" swapped="no"/>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkVBox" id="vbox3">
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">False</property>
                <child>
                  <object class="GtkHBox" id="hbox4">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <object class="GtkLabel" id="label4">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="label" translatable="yes">Username:</property>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkEntry" id="entry3">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="invisible_char">•</property>
                        <property name="primary_icon_activatable">False</property>
                        <property name="secondary_icon_activatable">False</property>
                        <property name="primary_icon_sensitive">True</property>
                        <property name="secondary_icon_sensitive">True</property>
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
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkHBox" id="hbox5">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <object class="GtkLabel" id="label5">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="label" translatable="yes">Password:</property>
                      </object>
                      <packing>
                        <property name="expand">False</property>
                        <property name="fill">False</property>
                        <property name="position">0</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkEntry" id="entry4">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="visibility">False</property>
                        <property name="invisible_char">•</property>
                        <property name="primary_icon_activatable">False</property>
                        <property name="secondary_icon_activatable">False</property>
                        <property name="primary_icon_sensitive">True</property>
                        <property name="secondary_icon_sensitive">True</property>
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
                    <property name="position">1</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkScrolledWindow" id="scrolledwindow2">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="hscrollbar_policy">automatic</property>
                <property name="vscrollbar_policy">automatic</property>
                <child>
                  <object class="GtkTreeView" id="treeview1">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="model">liststore1</property>
                    <property name="enable_grid_lines">both</property>
                    <signal name="button-press-event" handler="treeview1_button_press_event_cb" swapped="no"/>
                    <signal name="key-press-event" handler="on_treeview1_key_press_event" swapped="no"/>
                    <child>
                      <object class="GtkTreeViewColumn" id="treeviewcolumn1">
                        <property name="sizing">autosize</property>
                        <property name="title" translatable="yes">State</property>
                        <child>
                          <object class="GtkCellRendererPixbuf" id="cellrendererpixbuf1"/>
                          <attributes>
                            <attribute name="pixbuf">0</attribute>
                          </attributes>
                        </child>
                      </object>
                    </child>
                    <child>
                      <object class="GtkTreeViewColumn" id="treeviewcolumn2">
                        <property name="title" translatable="yes">URL path</property>
                        <child>
                          <object class="GtkCellRendererText" id="cellrenderertext1"/>
                          <attributes>
                            <attribute name="text">1</attribute>
                          </attributes>
                        </child>
                      </object>
                    </child>
                    <child>
                      <object class="GtkTreeViewColumn" id="treeviewcolumn3">
                        <property name="title" translatable="yes">Ouput path</property>
                        <child>
                          <object class="GtkCellRendererText" id="cellrenderertext2"/>
                          <attributes>
                            <attribute name="text">2</attribute>
                          </attributes>
                        </child>
                      </object>
                    </child>
                    <child>
                      <object class="GtkTreeViewColumn" id="treeviewcolumn4">
                        <property name="sizing">autosize</property>
                        <property name="title" translatable="yes">Operation type</property>
                        <child>
                          <object class="GtkCellRendererText" id="cellrenderertext3"/>
                          <attributes>
                            <attribute name="text">3</attribute>
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
                <property name="position">5</property>
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
          <object class="GtkScrolledWindow" id="scrolledwindow1">
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="hscrollbar_policy">automatic</property>
            <property name="vscrollbar_policy">automatic</property>
            <property name="shadow_type">out</property>
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
          <object class="GtkHBox" id="hbox3">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkButton" id="button4">
                <property name="label">gtk-ok</property>
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="on_button4_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="button2">
                <property name="label">gtk-clear</property>
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
                <property name="expand">True</property>
                <property name="fill">False</property>
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
