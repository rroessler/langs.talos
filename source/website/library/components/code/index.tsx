/// Package Modules
import { Client } from './client';
import { Server } from './server';

/** Code Component Namespace. */
export namespace Code {
    //  PROPERTIES  //

    /** Client Code-Block. */
    export type Block = Client;
    export const Block = Client;

    /** Dynamic Server Code-Block. */
    export type Dynamic = Server;
    export const Dynamic = Server;
}
