/// VSC Modules
import { Output } from '@/vscode/output';

/** Available Settings Schema. */
export interface Schema {
    'server.executablePath': string;
    'server.loggingLevel': Output.Level;
}
