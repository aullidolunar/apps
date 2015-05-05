<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <requires lib="gtk+" version="2.24"/>
  <!-- interface-naming-policy project-wide -->
  <object class="GtkAdjustment" id="adjustment1">
    <property name="lower">1</property>
    <property name="upper">120</property>
    <property name="value">1</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkWindow" id="window1">
    <property name="width_request">250</property>
    <property name="height_request">250</property>
    <property name="can_focus">False</property>
    <property name="window_position">center</property>
    <child>
      <object class="GtkVBox" id="vbox1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <child>
          <object class="GtkMenuBar" id="menubar1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkMenuItem" id="menuitem1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">_Application</property>
                <property name="use_underline">True</property>
                <child type="submenu">
                  <object class="GtkMenu" id="menu1">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <object class="GtkImageMenuItem" id="imagemenuitem1">
                        <property name="label">gtk-media-play</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                      </object>
                    </child>
                    <child>
                      <object class="GtkSeparatorMenuItem" id="separatormenuitem1">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="imagemenuitem2">
                        <property name="label">gtk-preferences</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                      </object>
                    </child>
                    <child>
                      <object class="GtkSeparatorMenuItem" id="separatormenuitem2">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                      </object>
                    </child>
                    <child>
                      <object class="GtkImageMenuItem" id="imagemenuitem3">
                        <property name="label">gtk-quit</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
            <child>
              <object class="GtkMenuItem" id="menuitem2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">_Help</property>
                <property name="use_underline">True</property>
                <child type="submenu">
                  <object class="GtkMenu" id="menu2">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <child>
                      <object class="GtkImageMenuItem" id="imagemenuitem4">
                        <property name="label">gtk-about</property>
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="use_underline">True</property>
                        <property name="use_stock">True</property>
                      </object>
                    </child>
                  </object>
                </child>
              </object>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkTable" id="table1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="border_width">10</property>
            <property name="n_rows">2</property>
            <property name="n_columns">2</property>
            <child>
              <object class="GtkLabel" id="label1">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="xalign">0</property>
                <property name="label" translatable="yes">Time elapsed</property>
              </object>
              <packing>
                <property name="x_options">GTK_FILL</property>
                <property name="y_options">GTK_SHRINK</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="label2">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="xalign">1</property>
                <property name="label">0</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="right_attach">2</property>
                <property name="x_options">GTK_FILL</property>
                <property name="y_options">GTK_SHRINK</property>
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
                  <object class="GtkTextView" id="textview1">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                    <property name="tooltip_text" translatable="yes">Something to remember</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="right_attach">2</property>
                <property name="top_attach">1</property>
                <property name="bottom_attach">2</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">True</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
  <object class="GtkDialog" id="dialog1">
    <property name="can_focus">False</property>
    <property name="border_width">5</property>
    <property name="window_position">center-on-parent</property>
    <property name="type_hint">dialog</property>
    <property name="transient_for">window1</property>
    <child internal-child="vbox">
      <object class="GtkVBox" id="dialog-vbox1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkHButtonBox" id="dialog-action_area1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="button1">
                <property name="label">gtk-ok</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="button2">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">1</property>
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
                  <object class="GtkTable" id="table2">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="n_rows">4</property>
                    <property name="n_columns">3</property>
                    <child>
                      <object class="GtkLabel" id="label4">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="xalign">0</property>
                        <property name="label" translatable="yes">Set minute timeout</property>
                      </object>
                      <packing>
                        <property name="y_options">GTK_EXPAND</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkCheckButton" id="checkbutton1">
                        <property name="label" translatable="yes">Enable notifications</property>
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="receives_default">False</property>
                        <property name="draw_indicator">True</property>
                      </object>
                      <packing>
                        <property name="right_attach">3</property>
                        <property name="top_attach">1</property>
                        <property name="bottom_attach">2</property>
                        <property name="y_options">GTK_EXPAND</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkHBox" id="hbox1">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <child>
                          <placeholder/>
                        </child>
                      </object>
                      <packing>
                        <property name="left_attach">1</property>
                        <property name="right_attach">2</property>
                        <property name="x_options">GTK_FILL</property>
                        <property name="y_options"/>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkSpinButton" id="spinbutton1">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="invisible_char">•</property>
                        <property name="xalign">1</property>
                        <property name="primary_icon_activatable">False</property>
                        <property name="secondary_icon_activatable">False</property>
                        <property name="primary_icon_sensitive">True</property>
                        <property name="secondary_icon_sensitive">True</property>
                        <property name="adjustment">adjustment1</property>
                        <property name="climb_rate">1</property>
                      </object>
                      <packing>
                        <property name="left_attach">2</property>
                        <property name="right_attach">3</property>
                        <property name="y_options"/>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkCheckButton" id="checkbutton2">
                        <property name="label" translatable="yes">Enable sounds</property>
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="receives_default">False</property>
                        <property name="draw_indicator">True</property>
                      </object>
                      <packing>
                        <property name="right_attach">3</property>
                        <property name="top_attach">2</property>
                        <property name="bottom_attach">3</property>
                        <property name="y_options">GTK_EXPAND</property>
                      </packing>
                    </child>
                    <child>
                      <object class="GtkCheckButton" id="checkbutton3">
                        <property name="label" translatable="yes">Reset timer on manual start</property>
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="receives_default">False</property>
                        <property name="draw_indicator">True</property>
                      </object>
                      <packing>
                        <property name="right_attach">3</property>
                        <property name="top_attach">3</property>
                        <property name="bottom_attach">4</property>
                        <property name="y_options">GTK_EXPAND</property>
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
                <property name="label" translatable="yes">&lt;b&gt;Preferences&lt;/b&gt;</property>
                <property name="use_markup">True</property>
              </object>
            </child>
          </object>
          <packing>
            <property name="expand">True</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="1">button1</action-widget>
      <action-widget response="0">button2</action-widget>
    </action-widgets>
  </object>
</interface>
