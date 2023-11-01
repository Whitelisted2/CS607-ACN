# Part 2 of CS607 - Assignment 3 (Project)

from pox.core import core
import pox.openflow.libopenflow_01 as of

log = core.getLogger()


class Firewall(object):
    """
    A Firewall object is created for each switch that connects.
    A Connection object for that switch is passed to the __init__ function.
    """

    def __init__(self, connection):
        # Keep track of the connection to the switch so that we can
        # send it messages!
        self.connection = connection

        # This binds our PacketIn event listener
        connection.addListeners(self)

        # add switch rules here
        self.icmp_entry()
        self.arp_entry()
        self.drop_entry()
    
    # flow table entry 1: ICMP [Highest priority, as per given table]
    def icmp_entry(self):
        fte_icmp = of.ofp_flow_mod()            # installs flow table entry

        fte_icmp.match.dl_type = 0x0800         # IPv4
        fte_icmp.match.nw_proto = 1             # ICMP

        action = of.ofp_action_output(port=of.OFPP_FLOOD)                   # flood all ports

        fte_icmp.actions.append(action)         # append action to flow table entry
        self.connection.send(fte_icmp)          # send command (OpenFlow) message to the switch

    # flow table entry 2: ARP [Second-highest priority, as per given table]
    def arp_entry(self):
        fte_arp = of.ofp_flow_mod()             # installs flow table entry

        fte_arp.match.dl_type = 0x0806          # ARP

        action = of.ofp_action_output(port=of.OFPP_FLOOD)                   # flood all ports

        fte_arp.actions.append(action)          # append action to flow table entry
        self.connection.send(fte_arp)           # send command (OpenFlow) message to the switch

    # flow table entry 3: Drop [Third-highest priority, as per given table]
    def drop_entry(self):
        fte_drop = of.ofp_flow_mod()             # installs flow table entry
        
        self.connection.send(fte_drop)           # send command (OpenFlow) message to the switch
        

    def _handle_PacketIn(self, event):
        """
        Packets not handled by the router rules will be
        forwarded to this method to be handled by the controller
        """

        packet = event.parsed  # This is the parsed packet data.
        if not packet.parsed:
            log.warning("Ignoring incomplete packet")
            return

        packet_in = event.ofp  # The actual ofp_packet_in message.
        print("Unhandled packet :" + str(packet.dump()))


def launch():
    """
    Starts the component
    """

    def start_switch(event):
        log.debug("Controlling %s" % (event.connection,))
        Firewall(event.connection)

    core.openflow.addListenerByName("ConnectionUp", start_switch)
