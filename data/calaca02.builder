<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <requires lib="gtk+" version="2.24"/>
  <!-- interface-naming-policy project-wide -->
  <object class="GtkWindow" id="window1">
    <property name="can_focus">False</property>
    <property name="window_position">center</property>
    <child>
      <object class="GtkTable" id="table1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="n_rows">5</property>
        <property name="n_columns">2</property>
        <child>
          <object class="GtkEntry" id="entry1">
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="invisible_char">•</property>
            <property name="primary_icon_activatable">False</property>
            <property name="secondary_icon_activatable">False</property>
            <property name="primary_icon_sensitive">True</property>
            <property name="secondary_icon_sensitive">True</property>
          </object>
          <packing>
            <property name="y_options">GTK_SHRINK</property>
            <property name="x_padding">10</property>
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
          </object>
          <packing>
            <property name="left_attach">1</property>
            <property name="right_attach">2</property>
            <property name="x_options">GTK_FILL</property>
            <property name="y_options">GTK_SHRINK</property>
            <property name="x_padding">10</property>
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
              <object class="GtkTreeView" id="treeview1">
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="border_width">10</property>
                <property name="headers_visible">False</property>
              </object>
            </child>
          </object>
          <packing>
            <property name="right_attach">2</property>
            <property name="top_attach">1</property>
            <property name="bottom_attach">2</property>
            <property name="x_padding">10</property>
            <property name="y_padding">10</property>
          </packing>
        </child>
        <child>
          <object class="GtkHSeparator" id="hseparator1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
          </object>
          <packing>
            <property name="right_attach">2</property>
            <property name="top_attach">3</property>
            <property name="bottom_attach">4</property>
            <property name="x_options">GTK_FILL</property>
            <property name="y_options">GTK_FILL</property>
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
            <property name="top_attach">4</property>
            <property name="bottom_attach">5</property>
            <property name="x_options">GTK_FILL</property>
            <property name="y_options">GTK_SHRINK</property>
          </packing>
        </child>
        <child>
          <object class="GtkButton" id="button2">
            <property name="label">gtk-execute</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="receives_default">True</property>
            <property name="use_stock">True</property>
          </object>
          <packing>
            <property name="left_attach">1</property>
            <property name="right_attach">2</property>
            <property name="top_attach">4</property>
            <property name="bottom_attach">5</property>
            <property name="x_options">GTK_SHRINK</property>
            <property name="y_options">GTK_SHRINK</property>
            <property name="x_padding">10</property>
            <property name="y_padding">10</property>
          </packing>
        </child>
        <child>
          <object class="GtkScrolledWindow" id="scrolledwindow2">
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="border_width">10</property>
            <property name="hscrollbar_policy">automatic</property>
            <property name="vscrollbar_policy">automatic</property>
            <property name="shadow_type">out</property>
            <child>
              <placeholder/>
            </child>
          </object>
          <packing>
            <property name="right_attach">2</property>
            <property name="top_attach">2</property>
            <property name="bottom_attach">3</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
