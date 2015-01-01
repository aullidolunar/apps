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
  <object class="GtkWindow" id="window1">
    <property name="can_focus">False</property>
    <property name="window_position">center</property>
    <signal name="destroy" handler="on_window1_destroy" swapped="no"/>
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
                <property name="shadow_type">out</property>
                <child>
                  <object class="GtkAlignment" id="alignment1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="top_padding">10</property>
                    <property name="bottom_padding">10</property>
                    <property name="left_padding">10</property>
                    <property name="right_padding">10</property>
                    <child>
                      <object class="GtkVBox" id="vbox3">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <child>
                          <object class="GtkComboBox" id="combobox1">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="model">liststore1</property>
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
                              <object class="GtkLabel" id="label3">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Value1</property>
                              </object>
                              <packing>
                                <property name="expand">False</property>
                                <property name="fill">False</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkEntry" id="entry1">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="invisible_char">•</property>
                                <property name="invisible_char_set">True</property>
                                <property name="primary_icon_activatable">False</property>
                                <property name="secondary_icon_activatable">False</property>
                                <property name="primary_icon_sensitive">True</property>
                                <property name="secondary_icon_sensitive">True</property>
                                <signal name="key-press-event" handler="on_entry1_key_press_event" swapped="no"/>
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
                        <child>
                          <object class="GtkHBox" id="hbox2">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <child>
                              <object class="GtkLabel" id="label4">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Value2</property>
                              </object>
                              <packing>
                                <property name="expand">False</property>
                                <property name="fill">False</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkEntry" id="entry2">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="invisible_char">•</property>
                                <property name="invisible_char_set">True</property>
                                <property name="primary_icon_activatable">False</property>
                                <property name="secondary_icon_activatable">False</property>
                                <property name="primary_icon_sensitive">True</property>
                                <property name="secondary_icon_sensitive">True</property>
                                <signal name="key-press-event" handler="on_entry2_key_press_event" swapped="no"/>
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
                            <property name="position">2</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel" id="label1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">&lt;b&gt;Operation&lt;/b&gt;</property>
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
              <object class="GtkVBox" id="vbox4">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
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
                      <object class="GtkEntry" id="entry3">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="invisible_char">•</property>
                        <property name="primary_icon_activatable">False</property>
                        <property name="secondary_icon_activatable">False</property>
                        <property name="primary_icon_sensitive">True</property>
                        <property name="secondary_icon_sensitive">True</property>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel" id="label2">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">&lt;b&gt;Result&lt;/b&gt;</property>
                    <property name="use_markup">True</property>
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
              <object class="GtkVBox" id="vbox5">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
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
          <object class="GtkHBox" id="hbox3">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkButton" id="button1">
                <property name="label">gtk-apply</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
                <signal name="clicked" handler="on_button1_clicked" swapped="no"/>
              </object>
              <packing>
                <property name="expand">True</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="button2">
                <property name="label">gtk-quit</property>
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
