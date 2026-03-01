/// Talos Modules
import { Dependency } from '@/talos/utilities';

/// Package Modules
import { Channel } from './channel';

/** Output Channel Interface. */
export const Service = Dependency.Name('output.service');
export interface Service {
    channel(): Channel;
    log(...args: any[]): void;
    debug(...args: any[]): void;
    info(...args: any[]): void;
    warn(...args: any[]): void;
    error(...args: any[]): void;
}
