/// Talos Modules
import { Dependency } from '@/talos/utilities';

/// Package Modules
import { Client } from './client';

/** Langauge Service Interface. */
export const Service = Dependency.Name('language.service');
export interface Service {
    restart(): Promise<void>;
    notify: InstanceType<typeof Client>['notify'];
    request: InstanceType<typeof Client>['request'];
}
